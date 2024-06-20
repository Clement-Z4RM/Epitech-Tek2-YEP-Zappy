/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** edi.c
*/

#include "../gui_commands.h"

void edi(uint64_t egg_id, clients_manager_t *clients_manager)
{
    char response[MAX_RESPONSE_SIZE];
    gui_client_node_t *node = NULL;

    snprintf(response, MAX_RESPONSE_SIZE, "edi %ld\n", egg_id);
    SLIST_FOREACH(node, &clients_manager->gui_clients_list, next)
    {
        client_add_request(node->client, response, TO_SEND);
    }
}
