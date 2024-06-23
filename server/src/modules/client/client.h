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

typedef enum client_type_e {
    NONE = -1,
    AI,
    GUI
} client_type_t;

typedef enum client_queue_type_e {
    TO_SEND,
    TO_HANDLE
} client_queue_type_t;

/**
* @brief represent a node of the client request queue received to handle
* @description
* this struct is used to represent a node
* of the client request queue to send
* it contains a request to handle and a pointer to the next node
* and a pointer to the previous node
**/
typedef struct client_request_node_s {
    char *request;
    CIRCLEQ_ENTRY(client_request_node_s) next;
} client_request_node_t;

CIRCLEQ_HEAD(client_requests_queue_s, client_request_node_s);
typedef struct client_requests_queue_s client_requests_queue_t;


/** @brief represent a client module **/
typedef struct client_s {
    int socket; ///< the socket of the client
    struct sockaddr_in *addr; ///< the address of the client
    char *team_name; ///< the team name of the client
    client_requests_queue_t requests_queue_to_send; ///< requests to send
    client_requests_queue_t requests_queue_to_handle; ///< requests to handle
    int requests_queue_to_send_size; ///< size requests to send
    int requests_queue_to_handle_size; ///< size requests to handle
    char *current_request_to_handle; ///< the current request being handled
    bool busy; ///< true if the client is busy, false otherwise
    client_type_t type; ///< the type of the client
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
* @param type the type of the request (to_send or to_handle)
* **/
extern void client_add_request(client_t *client,
    char *request, client_queue_type_t);

/**
* @brief send all requests contained in the requests queue
* @param client the client to send the requests from
* @param write_fds the file descriptor set for check writing
* @return bool true if the operation was successful, false otherwise (send)
**/
extern bool client_send_all_requests(client_t *client, fd_set *write_fds);

/**
* @brief pop a request from the client's request queue
* @param client the client to pop the request from
* @param type the type of the request to pop
* @return char* the request
*/
extern char *client_popback_request(client_t *client,
    client_queue_type_t type);
