/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** client module
*/

#pragma once
#include <sys/queue.h>
#include "stdbool.h"
#include <sys/socket.h>
#include <netinet/in.h>

/**
* @brief represent a node of the client request queue
* @description
* this struct is used to represent a node
* of the client request queue
* it contains a request to send and a pointer
* for the current tick to the next node
**/
typedef struct client_requests_node_s {
    char *request;
    SLIST_ENTRY(client_requests_node_s) next;
} client_request_node_t;

SLIST_HEAD(client_requests_queue_s, client_requests_node_s);
typedef struct client_requests_queue_s client_requests_queue_t;

/** @brief represent a client module **/
typedef struct client_s {
    int socket; ///< the socket of the client
    struct sockaddr_in *addr; ///< the address of the client
    char *team_name; ///< the team name of the client
    client_requests_queue_t requests_queue; ///< the queue of requests to send
} client_t;

/**
* @brief create a new instance of the module client
* @param socket the socket of the client
* @return client_t the newly allocated instance
* **/
extern client_t *client_constructor(int socket, struct sockaddr_in *addr);

/**
* @brief destroy a client instance
* @param client  the client to destroy
*/
extern void client_destructor(client_t *client);

/**
* @brief add a request to the client's request queue
* @param client the client to add the request to
* @param request the request to add
* **/
extern void client_add_request(client_t *client, char *request);

/**
* @brief send all requests contained in the requests queue
* @param client the client to send the requests from
* @param write_fds the file descriptor set for check writing
* @return bool true if the operation was successful, false otherwise (send)
**/
extern bool client_send_all_requests(client_t *client, fd_set *write_fds);
