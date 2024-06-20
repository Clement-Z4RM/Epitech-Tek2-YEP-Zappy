/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** ebo.c
*/

#include "../gui_commands.h"

void ebo(const uint64_t egg_id, const clients_manager_t *clients_manager)
{
    char response[MAX_RESPONSE_SIZE];
    gui_client_node_t *node = NULL;

    snprintf(response, MAX_RESPONSE_SIZE, "ebo %ld\n", egg_id);
    SLIST_FOREACH(node, &clients_manager->gui_clients_list, next)
    {
        client_add_request(node->client, response, TO_SEND);
    }
}
