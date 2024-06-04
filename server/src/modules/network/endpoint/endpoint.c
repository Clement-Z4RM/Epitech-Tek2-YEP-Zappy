/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** Endpoint submodule of network module
*/

#include "endpoint.h"
#include "stdlib.h"
#include "string.h"

static bool endpoint_init_socket(endpoint_t *endpoint)
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd == -1)
        return false;
    endpoint->socket = socket_fd;
    return true;
}

static void endpoint_init_address(endpoint_t *endpoint)
{
    endpoint->addr.sin_family = AF_INET;
    endpoint->addr.sin_port = htons(endpoint->port);
    endpoint->addr.sin_addr.s_addr = inet_addr(endpoint->ip);
}

static bool endpoint_bind_adress(endpoint_t *endpoint)
{
    if (endpoint->type == CLIENT)
        return true;
    if (bind(endpoint->socket, (struct sockaddr *)&endpoint->addr,
        sizeof(endpoint->addr)) == -1)
        return false;
    return true;
}

static bool endpoint_init_mode(endpoint_t *endpoint)
{
    if (endpoint->type == SERVER) {
        if (listen(endpoint->socket, 10) == -1)
            return false;
        return true;
    }
    if (connect(endpoint->socket, (struct sockaddr *)&endpoint->addr,
        sizeof(endpoint->addr)) == -1)
        return false;
    return true;
}

void endpoint_destructor(endpoint_t *endpoint)
{
    free(endpoint->ip);
    free(endpoint);
}

endpoint_t *endpoint_constructor(char *ip, int port, endpoint_type_t type)
{
    endpoint_t *endpoint = malloc(sizeof(endpoint_t));

    endpoint->ip = strdup(ip);
    endpoint->port = port;
    endpoint->type = type;
    if (!endpoint_init_socket(endpoint))
        return NULL;
    endpoint_init_address(endpoint);
    if (!endpoint_bind_adress(endpoint))
        return NULL;
    if (!endpoint_init_mode(endpoint))
        return NULL;
    return endpoint;
}
