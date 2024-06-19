/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** clients_manager
*/

#pragma once
#include <sys/queue.h>
#include "player/player.h"
#include "client/client.h"

/** @brief represent a node of the ai clients list **/
typedef struct ai_client_node_s {
    client_t *client;
    player_t player; // TODO: init using memset (and members that can be init)
    SLIST_ENTRY(ai_client_node_s) next;
} ai_client_node_t;

SLIST_HEAD(ai_clients_list_s, ai_client_node_s);
typedef struct ai_clients_list_s ai_clients_list_t;

/**@brief represent a node of the gui clients list **/
typedef struct gui_client_node_s {
    client_t *client;
    SLIST_ENTRY(gui_client_node_s) next;
} gui_client_node_t;

SLIST_HEAD(gui_clients_list_s, gui_client_node_s);
typedef struct gui_clients_list_s gui_clients_list_t;

/** @brief represent a node of the global clients list **/
typedef struct client_node_s {
    client_t *client;
    SLIST_ENTRY(client_node_s) next;
} client_node_t;

SLIST_HEAD(clients_list_s, client_node_s);
typedef struct clients_list_s clients_list_t;

/** @brief linked list of clients per team (ai) **/
typedef struct team_node_s {
    char *name;
    ai_clients_list_t *ai_clients;
    ulong nb_clients;
    SLIST_ENTRY(team_node_s) next;
} team_node_t;

SLIST_HEAD(team_list_s, team_node_s);
typedef struct team_list_s team_list_t;

/** @brief represent the client manager module **/
typedef struct clients_manager_s {
    clients_list_t clients_list; ///< the list of clients
    int nb_clients; ///< actual number of clients

    ai_clients_list_t ai_clients_list; ///< the list of ai clients
    int nb_ai_clients; ///< actual number of ai clients

    gui_clients_list_t gui_clients_list; ///< the list of gui clients
    int nb_gui_clients; ///< actual number of gui clients

    team_list_t team_list; ///< the list of teams
    int nb_teams; ///< actual number of teams

    ulong max_clients_per_team; ///< the maximum number of clients per team
} clients_manager_t;

/**
* @brief create a new instance of the clients_manager module
* @return clients_manager_t the newly allocated instance
* **/
clients_manager_t *clients_manager_constructor(ulong max_clients_per_team);

/**
 * @brief destroy a client manager instance and all its clients
 * @param manager the client manager to destroy
 */
extern void clients_manager_destructor(clients_manager_t *manager);

/**
* @brief add a new client to the client manager's list
* @param manager the client manager
* @param client the client to add
* @param type the type of the client
* **/
extern bool clients_manager_add(
    clients_manager_t *manager,
    client_t *client,
    const client_type_t type
);

/**
* @brief remove a client from the client manager's list
* @param manager the client manager
* @param client the client to remove
* **/
extern void clients_manager_remove(clients_manager_t *manager,
    client_t *client);

/**
 * @brief add a new ai client to the client manager's list
 * @param manager the client manager
 * @param client the client to add
 * @param team_name the team name of the client
 * @return bool true if the operation was successful, false otherwise
 */
extern bool clients_manager_add_to_team(
    clients_manager_t *manager,
    client_t *client,
    const char *team_name
);

/**
* @brief get a ai node from the client manager's list by id
* @param manager the client manager
* @param id the id of the ai client
* @return ai_client_node_t* the ai client node (NULL if not found)
* **/
extern ai_client_node_t *clients_manager_get_ai_by_id(
    clients_manager_t *manager, uint64_t id);
