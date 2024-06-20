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

bool add_new_team(clients_manager_t *manager, const char *team_name)
{
    team_node_t *curr_team = malloc(sizeof(team_node_t));

    if (curr_team == NULL) {
        perror("malloc");
        return false;
    }
    curr_team->name = strdup(team_name);
    curr_team->nb_clients = 0;
    SLIST_INIT(&curr_team->ai_clients);
    SLIST_INSERT_HEAD(&manager->team_list, curr_team, next);
    return true;
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
