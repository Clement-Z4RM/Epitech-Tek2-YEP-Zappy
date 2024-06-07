/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** Endpoint submodule of network module
*/

#include "endpoint.h"
#include "stdlib.h"
#include "string.h"

/**
* @brief initialize the socket of the endpoint
* @description
* the socket of the server is initialized with the socket function
* the socket is set to AF_INET (IPv4)
* the mode of the socket is set to SOCK_STREAM (TCP)
* the protocol is set to 0 (default protocol)
* @param endpoint the endpoint to initialize the socket
* @return bool true if the operation was successful, false otherwise
**/
static bool endpoint_init_socket(endpoint_t *endpoint)
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd == -1)
        return false;
    endpoint->socket = socket_fd;
    return true;
}

/**
* @brief initialize the address of the endpoint
* @description
* the address is initialized with the ip and port of the endpoint
* the address family is set to AF_INET
* the port is converted to network byte order
* the ip is converted to network byte order
* @param endpoint the endpoint to initialize the address
* **/
static void endpoint_init_address(endpoint_t *endpoint)
{
    endpoint->addr.sin_family = AF_INET;
    endpoint->addr.sin_port = htons(endpoint->port);
    endpoint->addr.sin_addr.s_addr = inet_addr(endpoint->ip);
}

/**
* @brief bind the address to the socket
* @description
* if the endpoint is a client, it will return true
* if the endpoint is a server, it will bind the address to the socket
* @param endpoint the endpoint to bind the address to
* @return bool true if the operation was successful, false otherwise
**/
static bool endpoint_bind_adress(endpoint_t *endpoint)
{
    if (endpoint->type == CLIENT)
        return true;
    if (bind(endpoint->socket, (struct sockaddr *)&endpoint->addr,
        sizeof(endpoint->addr)) == -1)
        return false;
    return true;
}

/**
* @brief initialize the mode of the endpoint
* @description
* if the endpoint is a server, it will listen
* if the endpoint is a client, it will connect
* @param endpoint the endpoint to initialize the mode
* @return bool true if the operation was successful, false otherwise
* **/
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
