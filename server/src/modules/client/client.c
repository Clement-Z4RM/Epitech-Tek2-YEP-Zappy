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
#include "unistd.h"

static void client_destroy_lists(client_t *client)
{
    client_request_node_t *current_send = NULL;
    client_request_node_t *current_receive = NULL;

    while (!CIRCLEQ_EMPTY(&client->requests_queue_to_send)) {
        current_send = CIRCLEQ_FIRST(&client->requests_queue_to_send);
        CIRCLEQ_REMOVE(&client->requests_queue_to_send, current_send, next);
        free(current_send->request);
        free(current_send);
    }
    while (!CIRCLEQ_EMPTY(&client->requests_queue_to_handle)) {
        current_receive = CIRCLEQ_FIRST(&client->requests_queue_to_handle);
        CIRCLEQ_REMOVE(&client->requests_queue_to_handle,
            current_receive, next);
        free(current_receive->request);
        free(current_receive);
    }
}

char *client_popback_request(client_t *client, client_queue_type_t type)
{
    char *request = NULL;
    client_request_node_t *current = NULL;

    if (type == TO_HANDLE) {
        current = CIRCLEQ_LAST(&client->requests_queue_to_handle);
        request = current->request;
        CIRCLEQ_REMOVE(&client->requests_queue_to_handle, current, next);
        free(current);
        client->requests_queue_to_handle_size--;
    } else if (type == TO_SEND) {
        current = CIRCLEQ_LAST(&client->requests_queue_to_send);
        request = current->request;
        CIRCLEQ_REMOVE(&client->requests_queue_to_send, current, next);
        free(current);
        client->requests_queue_to_send_size--;
    }
    return request;
}

bool client_send_all_requests(client_t *client, fd_set *write_fds)
{
    client_request_node_t *current = NULL;

    if (client == NULL || write_fds == NULL)
        return false;
    while (!CIRCLEQ_EMPTY(&client->requests_queue_to_send)) {
        current = CIRCLEQ_LAST(&client->requests_queue_to_send);
        if (!send(client->socket, current->request,
            strlen(current->request), 0)) {
            perror("send");
            return false;
        }
        CIRCLEQ_REMOVE(&client->requests_queue_to_send, current, next);
        free(current->request);
        free(current);
    }
    return true;
}

void client_add_request(client_t *client, char *request,
    client_queue_type_t type)
{
    client_request_node_t *new_node = malloc(sizeof(client_request_node_t));

    if (new_node == NULL)
        return;
    new_node->request = request;
    if (type == TO_HANDLE) {
        CIRCLEQ_INSERT_HEAD(&client->requests_queue_to_handle, new_node, next);
        client->requests_queue_to_handle_size++;
    } else if (type == TO_SEND) {
        CIRCLEQ_INSERT_HEAD(&client->requests_queue_to_send, new_node, next);
        client->requests_queue_to_send_size++;
    }
}

void client_destructor(client_t *client)
{
    if (client->team_name)
        free(client->team_name);
    client_destroy_lists(client);
    close(client->socket);
    free(client);
}

client_t *client_constructor(int socket, struct sockaddr_in *addr)
{
    client_t *client = malloc(sizeof(client_t));

    if (client == NULL) {
        perror("malloc");
        return NULL;
    }
    client->socket = socket;
    client->team_name = NULL;
    client->addr = addr;
    client->current_request_to_handle = NULL;
    client->requests_queue_to_send_size = 0;
    client->requests_queue_to_handle_size = 0;
    client->type = NONE;
    client->id = -1;
    CIRCLEQ_INIT(&client->requests_queue_to_send);
    CIRCLEQ_INIT(&client->requests_queue_to_handle);
    return client;
}
