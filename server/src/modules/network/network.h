/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** Network module
*/

#pragma once
#include "stdlib.h"
#include "endpoint/endpoint.h"
#include "sys/select.h"
#include "clients_manager/clients_manager.h"

/**
* @brief represent the network module
* @description
* The network module is responsible for creating and managing the network
* (sockets and connections)
**/
typedef struct network_s {
    endpoint_t *endpoint; ///< used to listen (ip, port, address)
    fd_set read_fds; ///< the file descriptor set for reading
    fd_set write_fds; ///< the file descriptor set for writing
    client_manager_t *clients_manager; //< the clients manager
} network_t;

/**
* @brief create a new instance of the network module
* @param ip the ip of the network server
* @param port the port of the network server
* @return network_t the newly allocated instance
**/
network_t *network_constructor(char *ip, int port);

/**
* @brief destroy a network instance (freeing memory)
* @param network the network to destroy
**/
void network_destructor(network_t *network);
