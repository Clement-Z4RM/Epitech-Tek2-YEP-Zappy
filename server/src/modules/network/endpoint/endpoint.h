/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** Endpoint submodule of network module
*/

#pragma once
#include <netinet/in.h>

/**
* @brief Enum endpoint_type
* @description
* Enum to represent the type of the endpoint (server or client)
**/
enum endpoint_type {
    SERVER,
    CLIENT // for scaling purposes(if the server need to connect another server)
};

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
    enum endpoint_type type;
    struct sockaddr_in addr;
} endpoint_t;
