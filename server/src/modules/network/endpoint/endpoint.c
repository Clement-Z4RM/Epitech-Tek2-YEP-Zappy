/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** Endpoint submodule of network module
*/

#include "endpoint.h"
#include "stdlib.h"
#include "string.h"

//TODO: add bind methods to bind address, listen and accept connexion

void endpoint_destructor(endpoint_t *endpoint)
{
    free(endpoint->ip);
    free(endpoint);
}

endpoint_t *endpoint_constructor(char *ip, int port)
{
    endpoint_t *endpoint = malloc(sizeof(endpoint_t));

    endpoint->ip = strdup(ip);
    endpoint->port = port;
    return endpoint;
}
