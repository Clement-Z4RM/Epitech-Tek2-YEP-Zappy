/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** clients_manager
*/

#pragma once
#include "../client/client.h"
#include "sys/queue.h"

typedef struct ai_client_node_s {
    client_t *client;
    SLIST_ENTRY(ai_client_node_s) next;
} ai_client_node_t;

SLIST_HEAD(ai_clients_list_s, ai_client_node_s);
typedef struct ai_clients_list_s ai_clients_list_t;

typedef struct gui_client_node_s {
    client_t *client;
    SLIST_ENTRY(gui_client_node_s) next;
} gui_client_node_t;

SLIST_HEAD(gui_clients_list_s, gui_client_node_s);
typedef struct gui_clients_list_s gui_clients_list_t;

/** @brief represent a node of the client list **/
typedef struct client_node_s {
    client_t *client;
    SLIST_ENTRY(client_node_s) next;
} client_node_t;

SLIST_HEAD(clients_list_s, client_node_s);
typedef struct clients_list_s clients_list_t;

/** @brief represent the client manager module **/
typedef struct clients_manager_s {
    clients_list_t clients_list; ///< the list of clients
    int nb_clients; ///< actual number of clients

    ai_clients_list_t ai_clients_list; ///< the list of ai clients
    int nb_ai_clients; ///< actual number of ai clients

    gui_clients_list_t gui_clients_list; ///< the list of gui clients
    int nb_gui_clients; ///< actual number of gui clients
} client_manager_t;

/**
* @brief create a new instance of the client_manager module
* @return client_manager_t the newly allocated instance
* **/
client_manager_t *clients_manager_constructor(void);

/**
 * @brief destroy a client manager instance and all its clients
 * @param manager the client manager to destroy
 */
extern void clients_manager_destructor(client_manager_t *manager);

/**
* @brief add a new client to the client manager's list
* @param manager the client manager
* @param client the client to add
* @param type the type of the client
* **/
extern bool clients_manager_add(
    client_manager_t *manager,
    client_t *client,
    const client_type_t type
);

/**
* @brief remove a client from the client manager's list
* @param manager the client manager
* @param client the client to remove
* **/
extern void clients_manager_remove(client_manager_t *manager,
    client_t *client);
