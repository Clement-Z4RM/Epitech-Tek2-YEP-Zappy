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
    endpoint_t *endpoint; //< the endpoint of the network
    fd_set read_fds; //< the file descriptor set for reading
    fd_set write_fds; //< the file descriptor set for writing
    client_manager_t *clients_manager; //< the clients manager
} network_t;
