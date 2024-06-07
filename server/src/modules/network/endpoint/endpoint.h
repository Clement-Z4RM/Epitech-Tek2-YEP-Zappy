/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** Endpoint submodule of network module
*/

#pragma once
#include <netinet/in.h>
#include "stdbool.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/**
* @brief Enum endpoint_type
* @description
* Enum to represent the type of the endpoint (server or client)
**/
typedef enum endpoint_type {
    SERVER,
    CLIENT // for scaling purposes (case of need to connect another server)
} endpoint_type_t;

/**
* @brief Endpoint module
* @description
* Represents a network endpoint (ip, port, socket, type) to be used to
* connect to a server or to bind a server
* **/
typedef struct endpoint_s {
    int socket;
    char *ip;
    int port;
    endpoint_type_t type;
    struct sockaddr_in addr;
} endpoint_t;

/**
* @brief create a new instance of the endpoint module
* @param ip the ip of the endpoint
* @param port the port of the endpoint
* @param type the type of the endpoint
* @return endpoint_t the newly allocated instance (or NULL if failed)
**/
endpoint_t *endpoint_constructor(char *ip, int port, endpoint_type_t type);

/**
* @brief destroy an endpoint instance (freeing memory)
* @param endpoint the endpoint to destroy
**/
void endpoint_destructor(endpoint_t *endpoint);
