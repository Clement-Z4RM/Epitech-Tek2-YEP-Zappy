/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** module used to manage clients
*/

#include "clients_manager.h"
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

//TODO: init the player struct with map or something
static bool add_ai(clients_manager_t *manager, client_t *client)
{
    ai_client_node_t *new_node = malloc(sizeof(ai_client_node_t));
    static uint64_t id = 0;

    if (new_node == NULL)
        return false;
    id++;
    new_node->player.id = id;
    new_node->player.level = 1;
    new_node->client = client;
    // TODO: init player
    SLIST_INSERT_HEAD(&manager->ai_clients_list, new_node, next);
    manager->nb_ai_clients++;
    return true;
}

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
    } else if (type == AI) {
        state = add_ai(manager, client);
    } else {
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

void clients_manager_destructor(clients_manager_t *manager)
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

clients_manager_t *clients_manager_constructor(ulong max_clients_per_team)
{
    clients_manager_t *manager = malloc(sizeof(clients_manager_t));

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
