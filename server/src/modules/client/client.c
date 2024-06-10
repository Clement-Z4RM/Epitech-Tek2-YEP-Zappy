/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** client_module
*/

#include "client.h"
#include <stdlib.h>
#include <stdio.h>
#include "string.h"

bool client_send_all_requests(client_t *client, fd_set *write_fds)
{
    client_request_node_t *current = NULL;

    if (!client || !write_fds)
        return false;
    while (!SLIST_EMPTY(&client->requests_queue)) {
        current = SLIST_FIRST(&client->requests_queue);
        if (FD_ISSET(client->socket, write_fds) &&
            send(client->socket, current->request,
            strlen(current->request), 0) == -1
        ) {
            perror("send");
            return false;
        }
        SLIST_REMOVE_HEAD(&client->requests_queue, next);
        free(current->request);
        free(current);
    }
    return true;
}

void client_add_request(client_t *client, char *request)
{
    client_request_node_t *new_node = malloc(sizeof(client_request_node_t));

    if (!new_node)
        return;
    new_node->request = request;
    SLIST_INSERT_HEAD(&client->requests_queue, new_node, next);
}

void client_destroy(client_t *client)
{
    client_request_node_t *current = NULL;

    if (client->team_name)
        free(client->team_name);
    while (!SLIST_EMPTY(&client->requests_queue)) {
        current = SLIST_FIRST(&client->requests_queue);
        SLIST_REMOVE_HEAD(&client->requests_queue, next);
        free(current->request);
        free(current);
    }
    free(client);
}

client_t *client_create(int socket)
{
    client_t *client = malloc(sizeof(client_t));

    if (!client) {
        perror("malloc");
        return NULL;
    }
    client->socket = socket;
    client->team_name = NULL;
    SLIST_INIT(&client->requests_queue);
    return client;
}
