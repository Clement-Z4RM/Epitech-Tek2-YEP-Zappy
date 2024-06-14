/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** module used to manage clients
*/

#include "clients_manager.h"
#include <stdlib.h>
#include "sys/queue.h"
#include "stdio.h"

bool clients_manager_add(client_manager_t *manager, client_t *client, const client_type_t type)
{
    client_node_t *new_node = NULL;
    ai_client_node_t *new_ai_node = NULL;
    gui_client_node_t *new_gui_node = NULL;

    if (type == NONE) {
        new_node = malloc(sizeof(client_node_t));
        if (new_node == NULL)
            return false;
        new_node->client = client;
        SLIST_INSERT_HEAD(&manager->clients_list, new_node, next);
        manager->nb_clients++;
    } else if (type == AI) {
        new_ai_node = malloc(sizeof(ai_client_node_t));
        if (new_ai_node == NULL)
            return false;
        new_ai_node->client = client;
        SLIST_INSERT_HEAD(&manager->ai_clients_list, new_ai_node, next);
        manager->nb_ai_clients++;
    } else {
        new_gui_node = malloc(sizeof(gui_client_node_t));
        if (new_gui_node == NULL)
            return false;
        new_gui_node->client = client;
        SLIST_INSERT_HEAD(&manager->gui_clients_list, new_gui_node, next);
        manager->nb_gui_clients++;
    }
    return true;
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

client_manager_t *clients_manager_constructor(void)
{
    client_manager_t *manager = malloc(sizeof(client_manager_t));

    if (!manager)
        return NULL;
    SLIST_INIT(&manager->clients_list);
    manager->nb_clients = 0;
    return manager;
}
