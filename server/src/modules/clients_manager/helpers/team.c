/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** team.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "logs/logs.h"
#include "player/player_methods.h"

void send_init_player_infos(ai_client_node_t *ai_client, map_t *map)
{
    char client_id_response[13];
    char map_response[23];

    snprintf(client_id_response, 13, "%lu\n", ai_client->player.id);
    snprintf(map_response, 23, "%lu %lu\n", map->x, map->y);
    client_add_request(ai_client->client, strdup(client_id_response), TO_SEND);
    client_add_request(ai_client->client, strdup(map_response), TO_SEND);
}

void clients_manager_team_destructor(team_node_t *team)
{
    team_egg_t *egg_current = NULL;
    ai_client_node_t *current = NULL;

    while (!SLIST_EMPTY(&team->eggs)) {
        egg_current = SLIST_FIRST(&team->eggs);
        SLIST_REMOVE_HEAD(&team->eggs, next);
        free(egg_current);
    }
    while (!SLIST_EMPTY(&team->ai_clients)) {
        current = SLIST_FIRST(&team->ai_clients);
        SLIST_REMOVE_HEAD(&team->ai_clients, next);
        client_destructor(current->client);
        free(current);
    }
    free(team->name);
    free(team);
}

/**
 * @brief initialize a team in the client manager's list
 *
 * @param manager the client manager
 * @param team_name the name of the team to initialize
 *
 * @return bool true if the operation was successful, false otherwise
 */
static bool add_new_team(clients_manager_t *manager, const char *team_name)
{
    team_node_t *curr_team = malloc(sizeof(team_node_t));

    if (curr_team == NULL) {
        perror("malloc");
        return false;
    }
    curr_team->name = strdup(team_name);
    SLIST_INIT(&curr_team->eggs);
    curr_team->nb_clients = 0;
    SLIST_INIT(&curr_team->ai_clients);
    SLIST_INSERT_HEAD(&manager->team_list, curr_team, next);
    return true;
}

void clients_manager_init_teams(clients_manager_t *manager,
    team_names_t *team_names)
{
    team_name_t *current = NULL;

    SLIST_FOREACH(current, team_names, next) {
        if (!add_new_team(manager, current->name)) {
            log_failure_init_team(current->name);
        } else {
            manager->nb_teams++;
            log_success_init_team(current->name);
        }
    }
}

static bool add_to_existing_team(
    clients_manager_t *manager,
    ai_client_node_t *ai_client,
    team_node_t *team,
    map_t *map
)
{
    static u_int64_t id = 1;

    if (team->nb_clients >= manager->max_clients_per_team) {
        log_failure_team_full(team->name);
        return false;
    }
    initialize_player(ai_client, map, team, id);
    ++id;
    SLIST_INSERT_HEAD(&team->ai_clients, ai_client, next);
    team->nb_clients++;
    manager->nb_ai_clients++;
    if (manager->is_game_started)
        send_init_player_infos(ai_client, map);
    return true;
}

bool clients_manager_add_to_team(
    clients_manager_t *manager,
    client_t *client,
    const char *team_name,
    map_t *map
)
{
    team_node_t *curr_team = SLIST_FIRST(&manager->team_list);
    ai_client_node_t *ai_client = malloc(sizeof(ai_client_node_t));

    if (ai_client == NULL)
        return false;
    ai_client->client = client;
    while (curr_team != NULL) {
        if (strcmp(curr_team->name, team_name) == 0)
            return add_to_existing_team(manager, ai_client, curr_team, map);
        curr_team = SLIST_NEXT(curr_team, next);
    }
    free(ai_client);
    return false;
}
