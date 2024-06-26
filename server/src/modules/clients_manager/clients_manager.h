/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** clients_manager
*/

#pragma once
#include <sys/queue.h>
#include "egg/egg.h"
#include "player/player.h"
#include "client/client.h"
#include "options/options.h"

/**
 * @brief map_t definition for circular dependencies
 * (is we include map.h, it doesn't compile)
 */
typedef struct map_s map_t;

/**
 * @brief Incantations list
 */
SLIST_HEAD(incantations_s, incantation_s);
typedef struct incantations_s incantations_t;

/** @brief represent a node of the ai clients list **/
typedef struct ai_client_node_s {
    client_t *client;
    player_t player;
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
    team_eggs_t eggs;
    ulong nb_eggs;
    ai_clients_list_t ai_clients;
    ulong nb_clients;
    SLIST_ENTRY(team_node_s) next;
} team_node_t;

SLIST_HEAD(team_list_s, team_node_s);
typedef struct team_list_s team_list_t;

/** @brief represent the client manager module **/
typedef struct clients_manager_s {
    clients_list_t clients_list; ///< the list of clients
    int nb_clients; ///< actual number of clients

    gui_clients_list_t gui_clients_list; ///< the list of gui clients
    int nb_gui_clients; ///< actual number of gui clients

    team_list_t team_list; ///< the list of teams
    int nb_teams; ///< actual number of teams

    incantations_t incantations; ///< the list of incantations

    bool is_game_started; ///< true if the game has started
} clients_manager_t;

/**
* @brief create a new instance of the clients_manager module
* @param options the server options
* @param map the map of the server
* @return clients_manager_t the newly allocated instance
* **/
extern clients_manager_t *clients_manager_constructor(
    options_t *options,
    map_t *map
);

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
    client_type_t type
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
 * @param map the map of the server
 * @return bool true if the operation was successful, false otherwise
 */
extern bool clients_manager_add_to_team(
    clients_manager_t *manager,
    client_t *client,
    const char *team_name,
    map_t *map
);

/**
* @brief get a ai node from the client manager's list by id
* @param manager the client manager
* @param id the id of the ai client
* @return ai_client_node_t* the ai client node (NULL if not found)
* **/
extern ai_client_node_t *clients_manager_get_ai_by_id(
    clients_manager_t *manager,
    uint64_t id
);

/**
 * @brief Get the team of a client.
 *
 * @param manager The clients manager where to search the team.
 * @param client The client to search the team of.
 *
 * @return The team of the client,
 * or NULL if the client is not in a team or if the team is not found.
 */
extern team_node_t *clients_manager_get_team_by_client(
    clients_manager_t *manager,
    ai_client_node_t *client
);

/**
 * @brief Destroy a team and all its clients and members
 *
 * @param team The team to destroy
 */
extern void clients_manager_team_destructor(team_node_t *team);

/**
 * @brief Initialize all teams in the client manager's list
 *
 * @param manager The client manager
 * @param team_names The list of team names
 */
extern void clients_manager_init_teams(
    clients_manager_t *manager,
    team_names_t *team_names
);

/**
 * @brief Spawn egg on the map and assign it to a team at a given position
 *
 * @param map The map where to spawn the egg
 * @param team The team to assign the egg to
 * @param x The column where to spawn the egg
 * @param y The row where to spawn the egg
 *
 * @return true if the operation was successful,
 * false otherwise (allocation error)
 */
extern bool spawn_egg(
    map_t *map,
    team_node_t **team,
    u_int64_t x,
    u_int64_t y
);

/**
 * @brief Initialize all eggs on the map and assign them to teams
 * spreading them evently
 *
 * @param manager The clients manager
 * @param options The server options
 * @param map The map of the server
 *
 * @return true if the operation was successful,
 * false otherwise (allocation error)
 */
extern bool client_manager_init_eggs(
    clients_manager_t *manager,
    options_t *options,
    map_t *map
);

extern void send_default_eggs(
    team_node_t *team,
    client_t *client
);


extern void send_init_player_infos(ai_client_node_t *ai_client, map_t *map,
    clients_manager_t *clients_manager);
