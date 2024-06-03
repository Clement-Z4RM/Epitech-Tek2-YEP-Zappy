/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** module used to manage clients
*/

#include "clients_manager.h"
#include <stdlib.h>

void client_manager_add_client(client_manager_t *manager, client_t *client)
{
    client_node_t *new_node = malloc(sizeof(client_node_t));

    if (!new_node)
        return;
    new_node->client = client;
    new_node->next = manager->clients_list;
    manager->clients_list = new_node;
    manager->nb_clients++;
}

void client_manager_remove_client(client_manager_t *manager, client_t *client)
{
    client_node_t *current = manager->clients_list;
    client_node_t *prev = NULL;

    while (current) {
        if (current->client == client)
            break;
        prev = current;
        current = current->next;
    }
    if (!current)
        return;
    if (prev)
        prev->next = current->next;
    else
        manager->clients_list = current->next;
}

void client_manager_destroy(client_manager_t *manager)
{
    client_node_t *next = NULL;

    for (client_node_t *current = manager->clients_list; current;) {
        next = current->next;
        client_destroy(current->client);
        free(current);
        current = next;
    }
    free(manager);
}

client_manager_t *client_manager_create(void)
{
    client_manager_t *manager = malloc(sizeof(client_manager_t));

    if (!manager)
        return NULL;
    manager->clients_list = NULL;
    manager->nb_clients = 0;
    return manager;
}
