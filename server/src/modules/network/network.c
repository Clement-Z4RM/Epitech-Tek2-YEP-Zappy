/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** Network module
*/

#include "network.h"
#include <stdio.h>

bool network_accept_connexion(network_t *network)
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
    client = client_create(client_socket);
    if (client == NULL) {
        return false;
    }
    clients_manager_add(network->clients_manager, client);
    printf("New client connected\n");
    return true;
}

bool network_set_and_select_fds(network_t *network)
{
    struct client_node_s *current = NULL;
    struct timeval timeout = {0};

    timeout.tv_sec = 0;
    timeout.tv_usec = 100;
    FD_ZERO(&network->read_fds);
    FD_ZERO(&network->write_fds);
    FD_SET(network->endpoint->socket, &network->read_fds);
    SLIST_FOREACH(current, &network->clients_manager->clients_list, next)
    {
        FD_SET(current->client->socket, &network->read_fds);
        FD_SET(current->client->socket, &network->write_fds);
    }
    if (select(FD_SETSIZE,
            &network->read_fds, &network->write_fds,
            NULL, &timeout) < 0) {
        perror("select");
        return false;
    }
    return true;
}

void network_destructor(network_t *network)
{
    if (network->endpoint)
        endpoint_destructor(network->endpoint);
    if (network->clients_manager)
        clients_manager_destructor(network->clients_manager);
    free(network);
}

network_t *network_constructor(char *ip, int port)
{
    network_t *network = malloc(sizeof(network_t));

    if (network == NULL) {
        perror("malloc");
        return NULL;
    }
    network->endpoint = endpoint_constructor(ip, port, SERVER);
    if (network->endpoint == NULL) {
        free(network);
        return NULL;
    }
    network->clients_manager = clients_manager_constructor();
    if (network->clients_manager == NULL) {
        network_destructor(network);
        return NULL;
    }
    return network;
}
