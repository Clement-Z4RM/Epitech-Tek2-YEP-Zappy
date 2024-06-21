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
#include "responses.h"
#include "../options/options.h"

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
    clients_manager_t *clients_manager; //< the clients manager
    options_t *options;
    void (*destroy)(struct network_s *network); ///< the destructor
} network_t;

/**
* @brief create a new instance of the network module
* @param ip the ip of the network server
* @param options the options of the server
* @param map the map of the server
* @return network_t the newly allocated instance
**/
extern network_t *network_constructor(
    char *ip,
    options_t *options,
    map_t *map
);

/**
* @brief set the file descriptors and select them
* @description
* This function is responsible for setting the file descriptors and selecting
* them for reading and writing, file descriptors are the socket of the server
* (endpoint) and the sockets of the clients
* socket of the clients is set for both reading and writing
* @param network the network to set and select the fds
*
* @return 0 on success, EINTR if interrupted, -1 otherwise (select error)
**/
extern int8_t network_set_and_select_fds(network_t *network);

/**
* @brief receive requests from clients and handle it with the request_manager
* @param network the network to receive requests from
* @return bool true if the operation was successful, false otherwise (recv)
*/
extern bool network_receive_requests(network_t *network);

/**
* @brief for each clients send all requests contained in the requests queue
* @param network the network to send requests from
* @param client the client to send requests to
* @param request the request to send
* @return bool true if the operation was successful, false otherwise (send)
**/
extern bool network_send_requests(network_t *network);
