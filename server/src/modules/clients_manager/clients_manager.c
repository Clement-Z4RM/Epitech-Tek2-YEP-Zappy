/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** module used to manage clients
*/

#include <sys/queue.h>
#include <stdlib.h>
#include <string.h>
#include "clients_manager.h"

static bool add_gui(clients_manager_t *manager, client_t *client)
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
    clients_manager_t *manager,
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
    } else if (type == GUI) {
        state = add_gui(manager, client);
    }
    return state;
}

//TODO: remove from every list
void clients_manager_remove(clients_manager_t *manager, client_t *client)
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

static void clients_manager_teams_destructor(clients_manager_t *manager)
{
    team_node_t *team_current = NULL;

    while (!SLIST_EMPTY(&manager->team_list)) {
        team_current = SLIST_FIRST(&manager->team_list);
        SLIST_REMOVE_HEAD(&manager->team_list, next);
        clients_manager_team_destructor(team_current);
    }
}

void clients_manager_destructor(clients_manager_t *manager)
{
    client_node_t *current = NULL;
    gui_client_node_t *gui_current = NULL;

    while (!SLIST_EMPTY(&manager->clients_list)) {
        current = SLIST_FIRST(&manager->clients_list);
        SLIST_REMOVE_HEAD(&manager->clients_list, next);
        client_destructor(current->client);
        free(current);
    }
    while (!SLIST_EMPTY(&manager->gui_clients_list)) {
        gui_current = SLIST_FIRST(&manager->gui_clients_list);
        SLIST_REMOVE_HEAD(&manager->gui_clients_list, next);
        client_destructor(gui_current->client);
        free(gui_current);
    }
    clients_manager_teams_destructor(manager);
    free(manager);
}

clients_manager_t *clients_manager_constructor(ulong max_clients_per_team,
    team_names_t *team_names)
{
    clients_manager_t *manager = malloc(sizeof(clients_manager_t));

    if (manager == NULL)
        return NULL;
    SLIST_INIT(&manager->clients_list);
    SLIST_INIT(&manager->gui_clients_list);
    SLIST_INIT(&manager->team_list);
    manager->nb_clients = 0;
    manager->nb_gui_clients = 0;
    manager->nb_teams = 0;
    manager->max_clients_per_team = max_clients_per_team;
    clients_manager_init_teams(manager, team_names);
    return manager;
}
