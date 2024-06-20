/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** pgt command
*/

#include "../gui_commands.h"

void pgt(const uint64_t id, resource_name_t resource, clients_manager_t
    *client_manager)
{
    char response[MAX_RESPONSE_SIZE];
    gui_client_node_t *node = NULL;

    snprintf(response, MAX_RESPONSE_SIZE, "pgt #%lu %d\n", id, resource);
    SLIST_FOREACH(node, &client_manager->gui_clients_list, next)
    {
        client_add_request(node->client, response, TO_SEND);
    }
}
