/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** pfk.c
*/

#include "../gui_commands.h"

void pfk(const uint64_t id, const client_manager_t *client_manager)
{
    char response[MAX_RESPONSE_SIZE];
    gui_client_node_t *node = NULL;

    snprintf(response, MAX_RESPONSE_SIZE, "pfk #%lu\n", id);
    SLIST_FOREACH(node, &client_manager->gui_clients_list, next)
    {
        client_add_request(node->client, response, TO_SEND);
    }
}
