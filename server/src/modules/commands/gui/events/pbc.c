/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** pbc (broadcast) command
*/

#include "../gui_commands.h"

void pbc(const uint64_t id, char *msg, const clients_manager_t *client_manager)
{
    char response[MAX_RESPONSE_SIZE];
    gui_client_node_t *node = NULL;

    snprintf(response, MAX_RESPONSE_SIZE, "pbc #%lu %s\n", id, msg);
    SLIST_FOREACH(node, &client_manager->gui_clients_list, next)
    {
        client_add_request(node->client, response, TO_SEND);
    }
}
