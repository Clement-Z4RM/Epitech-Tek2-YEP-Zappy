/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** client_manager module getters
*
*/

#include "clients_manager.h"
#include "stdlib.h"

ai_client_node_t *clients_manager_get_ai_by_id(
    client_manager_t *manager, uint64_t id)
{
    ai_client_node_t *node = NULL;

    SLIST_FOREACH(node, &manager->ai_clients_list, next)
    {
        if (node->player.id == id)
            return node;
    }
    return NULL;
}
