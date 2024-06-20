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

static void free_and_perror_malloc(team_node_t *team, ai_client_node_t *node)
{
    free(team);
    free(node);
    perror("malloc");
}

static bool add_new_team(
    clients_manager_t *manager,
    const char *team_name,
    client_t *client
)
{
    team_node_t *curr_team = malloc(sizeof(team_node_t));
    ai_client_node_t *new_node = malloc(sizeof(ai_client_node_t));

    if (curr_team == NULL || new_node == NULL) {
        free_and_perror_malloc(curr_team, new_node);
        return false;
    }
    curr_team->name = strdup(team_name);
    curr_team->nb_clients = 1;
    curr_team->ai_clients = malloc(sizeof(ai_clients_list_t));
    if (curr_team->ai_clients == NULL) {
        free_and_perror_malloc(curr_team, new_node);
        return false;
    }
    SLIST_INIT(curr_team->ai_clients);
    new_node->client = client;
    // TODO: init player
    SLIST_INSERT_HEAD(curr_team->ai_clients, new_node, next);
    SLIST_INSERT_HEAD(&manager->team_list, curr_team, next);
    return true;
}

static bool add_to_existing_team(
    clients_manager_t *manager,
    client_t *client,
    team_node_t *team
)
{
    ai_client_node_t *new_node;

    if (team->nb_clients >= manager->max_clients_per_team) {
        log_failure_team_full(team->name);
        return false;
    }
    new_node = malloc(sizeof(ai_client_node_t));
    if (new_node == NULL)
        return false;
    new_node->client = client;
    // TODO: init player
    SLIST_INSERT_HEAD(team->ai_clients, new_node, next);
    team->nb_clients++;
    return true;
}

bool clients_manager_add_to_team(
    clients_manager_t *manager,
    client_t *client,
    const char *team_name
)
{
    team_node_t *curr_team = SLIST_FIRST(&manager->team_list);

    while (curr_team != NULL) {
        if (strcmp(curr_team->name, team_name) == 0) {
            return add_to_existing_team(
                manager,
                client,
                curr_team
            );
        }
        curr_team = SLIST_NEXT(curr_team, next);
    }
    return add_new_team(manager, team_name, client);
}
