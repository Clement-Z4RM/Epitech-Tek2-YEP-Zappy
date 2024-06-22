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

#define ENDPOINT_IP "127.0.0.1"

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
    int port;
    endpoint_type_t type;
    struct sockaddr_in addr;
} endpoint_t;

/**
* @brief create a new instance of the endpoint module
* @param endpoint the endpoint structure to fill
* @param port the port of the endpoint
* @param type the type of the endpoint
* @return bool true if the operation was successful, false otherwise
**/
extern bool endpoint_constructor(
    endpoint_t *endpoint,
    int port,
    endpoint_type_t type
);
