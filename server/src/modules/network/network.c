/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** Network module
*/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "macros.h"
#include "requests_manager/requests_manager.h"
#include "logs/logs.h"
#include "network.h"

/**
* @brief accept a new client connection
* @description
* This function is responsible for accepting a new client connection
* It creates a new client instance and adds it to the clients manager
* @param network the network to accept the connection
* @return bool true if the operation was successful, false otherwise (accept)
**/
static bool network_accept_connexion(network_t *network)
{
    struct sockaddr_in client_address = {0};
    client_t *client = NULL;
    socklen_t client_address_size = sizeof(client_address);
    int client_socket = accept(network->endpoint->socket,
        (struct sockaddr *)&client_address, &client_address_size);

    if (client_socket == -1) {
        perror("accept");
        return false;
    }
    client = client_constructor(client_socket, &client_address);
    if (client == NULL)
        return false;
    if (!clients_manager_add(network->clients_manager, client, NONE))
        return false;
    client_add_request(client, RQST_WELCOME, TO_SEND);
    log_success_network_client_connected(client);
    return true;
}

bool network_send_requests(network_t *network)
{
    client_node_t *current = NULL;

    SLIST_FOREACH(current, &network->clients_manager->clients_list, next) {
        if (!client_send_all_requests(current->client, &network->write_fds))
            return false;
    }
    return true;
}

bool network_receive_requests(network_t *network)
{
    struct client_node_s *current = NULL;
    char buffer[1024] = {0};

    if (FD_ISSET(network->endpoint->socket, &network->read_fds)) {
        if (!network_accept_connexion(network))
            return false;
    }
    SLIST_FOREACH(current, &network->clients_manager->clients_list, next)
    {
        if (FD_ISSET(current->client->socket, &network->read_fds) &&
            current->client->requests_queue_to_handle_size < 10) {
            if (recv(current->client->socket, buffer, 1024, 0) == -1) {
                perror("recv");
                return false;
            }
            if (current->client->requests_queue_to_handle_size < 10)
                client_add_request(current->client, strdup(buffer), TO_HANDLE);
        }
    }
    return true;
}

int8_t network_set_and_select_fds(network_t *network)
{
    struct client_node_s *current = NULL;
    struct timeval timeout = {0, 100};

    FD_ZERO(&network->read_fds);
    FD_ZERO(&network->write_fds);
    FD_SET(network->endpoint->socket, &network->read_fds);
    SLIST_FOREACH(current, &network->clients_manager->clients_list, next) {
        FD_SET(current->client->socket, &network->read_fds);
        FD_SET(current->client->socket, &network->write_fds);
    }
    if (select(FD_SETSIZE,
            &network->read_fds, &network->write_fds,
            NULL, &timeout) < 0) {
        if (errno == EINTR)
            return EINTR;
        perror("select");
        return ERROR;
    }
    return SUCCESS;
}

static void network_destructor(network_t *network)
{
    if (network->endpoint)
        endpoint_destructor(network->endpoint);
    if (network->clients_manager)
        clients_manager_destructor(network->clients_manager);
    free(network);
}

static bool initialize_network(
    network_t *network,
    char *ip,
    options_t *options,
    map_t *map
)
{
    network->endpoint = endpoint_constructor(ip, options->port, SERVER);
    if (network->endpoint == NULL) {
        free(network);
        return false;
    }
    network->clients_manager = clients_manager_constructor(options, map);
    if (network->clients_manager == NULL) {
        network_destructor(network);
        return false;
    }
    network->options = options;
    network->destroy = &network_destructor;
    return true;
}

network_t *network_constructor(char *ip, options_t *options, map_t *map)
{
    network_t *network;

    if (!map)
        return NULL;
    network = malloc(sizeof(network_t));
    if (network == NULL) {
        perror("malloc");
        return NULL;
    }
    if (!initialize_network(network, ip, options, map))
        return NULL;
    return network;
}
