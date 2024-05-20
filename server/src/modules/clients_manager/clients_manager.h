/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** clients_manager
*/

#pragma once
#include "../client/client.h"

/** @brief represent a node of the client list (containing a client instance module) **/
typedef struct client_node_s {
    client_t *client;
    struct client_node_s *next;
} client_node_t;

/** @brief represent the client manager module **/
typedef struct client_manager_s {
    client_node_t *clients_list; //< list of clients
    int nb_clients; //< actual number of clients
} client_manager_t;

/**
* @brief create a new instance of the client_manager module
* @return client_manager_t the newly allocated instance
* **/
client_manager_t *client_manager_create(void);
