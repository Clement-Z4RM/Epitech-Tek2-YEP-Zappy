/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** module used to manage clients
*/

#include "clients_manager.h"
#include <stdlib.h>
#include <string.h>

#include "sys/queue.h"
#include "stdio.h"
#include "logs/failures/logs_failures.h"

static bool clients_manager_add_new_team(
    client_manager_t *manager,
    const char *team_name,
    client_t *client
)
{
    team_node_t *curr_team = malloc(sizeof(team_node_t));
    ai_client_node_t *new_node = malloc(sizeof(ai_client_node_t));

    if (curr_team == NULL || new_node == NULL) {
        perror("malloc");
        return false;
    }
    curr_team->name = strdup(team_name);
    curr_team->nb_clients = 1;
    curr_team->ai_clients = malloc(sizeof(ai_clients_list_t));
    if (curr_team->ai_clients == NULL) {
        perror("malloc");
        return false;
    }
    SLIST_INIT(curr_team->ai_clients);
    new_node->client = client;
    SLIST_INSERT_HEAD(curr_team->ai_clients, new_node, next);
    SLIST_INSERT_HEAD(&manager->team_list, curr_team, next);
    return true;
}

static bool clients_manager_add_to_existing_team(
    client_manager_t *manager,
    client_t *client,
    team_node_t *team
)
{
    ai_client_node_t *new_node = malloc(sizeof(ai_client_node_t));

    if (team->nb_clients >= manager->max_clients_per_team) {
        log_failure_team_full(team->name);
        return false;
    }
    if (new_node == NULL)
        return false;
    new_node->client = client;
    SLIST_INSERT_HEAD(team->ai_clients, new_node, next);
    team->nb_clients++;
    return true;
}

bool clients_manager_add_to_team(
    client_manager_t *manager,
    client_t *client,
    const char *team_name
)
{
    team_node_t *curr_team = SLIST_FIRST(&manager->team_list);

    while (curr_team != NULL) {
        if (strcmp(curr_team->name, team_name) == 0) {
            return clients_manager_add_to_existing_team(
                manager,
                client,
                curr_team
            );
        }
        curr_team = SLIST_NEXT(curr_team, next);
    }
    return clients_manager_add_new_team(manager, team_name, client);
}

static bool clients_manager_add_ai(client_manager_t *manager, client_t *client)
{
    ai_client_node_t *new_node = malloc(sizeof(ai_client_node_t));

    if (new_node == NULL)
        return false;
    new_node->client = client;
    SLIST_INSERT_HEAD(&manager->ai_clients_list, new_node, next);
    manager->nb_ai_clients++;
    return true;
}

static bool clients_manager_add_gui(
    client_manager_t *manager,
    client_t *client
)
{
    gui_client_node_t *new_node = malloc(sizeof(gui_client_node_t));

    if (new_node == NULL)
        return false;
    new_node->client = client;
    SLIST_INSERT_HEAD(&manager->gui_clients_list, new_node, next);
    manager->nb_gui_clients++;
    return true;
}

//TODO: exit here or return to main routine exiting if malloc failed ?
bool clients_manager_add(
    client_manager_t *manager,
    client_t *client,
    const client_type_t type
)
{
    client_node_t *new_node = NULL;
    bool state = true;

    client->type = type;
    if (type == NONE) {
        new_node = malloc(sizeof(client_node_t));
        if (new_node == NULL)
            return false;
        new_node->client = client;
        SLIST_INSERT_HEAD(&manager->clients_list, new_node, next);
        manager->nb_clients++;
    } else if (type == AI) {
        state = clients_manager_add_ai(manager, client);
    } else {
        state = clients_manager_add_gui(manager, client);
    }
    return state;
}

void clients_manager_remove(client_manager_t *manager, client_t *client)
{
    client_node_t *current = NULL;
    client_node_t *tmp = NULL;

    for (current = SLIST_FIRST(&manager->clients_list); current;
        current = SLIST_NEXT(current, next)) {
        if (current->client == client) {
            tmp = current;
            break;
        }
    }
    if (tmp) {
        SLIST_REMOVE(&manager->clients_list, tmp, client_node_s, next);
        client_destructor(tmp->client);
        free(tmp);
        manager->nb_clients--;
    }
}

void clients_manager_destructor(client_manager_t *manager)
{
    client_node_t *current = NULL;

    while (!SLIST_EMPTY(&manager->clients_list)) {
        current = SLIST_FIRST(&manager->clients_list);
        SLIST_REMOVE_HEAD(&manager->clients_list, next);
        client_destructor(current->client);
        free(current);
    }
    free(manager);
}

client_manager_t *clients_manager_constructor(ulong max_clients_per_team)
{
    client_manager_t *manager = malloc(sizeof(client_manager_t));

    if (manager == NULL)
        return NULL;
    SLIST_INIT(&manager->clients_list);
    SLIST_INIT(&manager->ai_clients_list);
    SLIST_INIT(&manager->gui_clients_list);
    SLIST_INIT(&manager->team_list);
    manager->nb_clients = 0;
    manager->nb_ai_clients = 0;
    manager->nb_gui_clients = 0;
    manager->nb_teams = 0;
    manager->max_clients_per_team = max_clients_per_team;
    return manager;
}
