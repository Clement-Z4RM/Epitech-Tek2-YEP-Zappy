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

/**
* @brief set the file descriptors and select them
* @description
* This function is responsible for setting the file descriptors and selecting
* them for reading and writing, file descriptors are the socket of the server
* (endpoint) and the sockets of the clients
* socket of the clients is set for both reading and writing
* @param network the network to set and select the fds
* @return bool true if the operation was successful, false otherwise (select)
**/
bool network_set_and_select_fds(network_t *network);

/**
* @brief receive requests from clients and handle it with the request_manager
* @param network the network to receive requests from
* @return bool true if the operation was successful, false otherwise (recv)
*/
bool network_receive_requests(network_t *network);

/**
 * @brief send a request to a client
 * @param network the network endpoint to send the request from
 * @param client the client to send the request to
 * @param request the request to send
 * @return bool true if the operation was successful, false otherwise (send)
 */
bool network_send_request(network_t *network, client_t *client, char *request);
