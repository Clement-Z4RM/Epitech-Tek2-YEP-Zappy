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

void clients_manager_add(client_manager_t *manager, client_t *client)
{
    client_node_t *new_node = malloc(sizeof(client_node_t));

    if (!new_node)
        return;
    new_node->client = client;
    SLIST_INSERT_HEAD(&manager->clients_list, new_node, next);
    manager->nb_clients++;
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
