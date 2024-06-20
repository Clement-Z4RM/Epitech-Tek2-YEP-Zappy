/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** enw command
*/

#include "../gui_commands.h"

void enw(const uint64_t egg_id, const uint64_t player_id,
    const clients_manager_t *clients_manager, const coords_t *coords)
{
    char response[MAX_RESPONSE_SIZE];
    gui_client_node_t *node = NULL;

    snprintf(response, MAX_RESPONSE_SIZE, "enw #%lu #%lu %zu %zu\n", egg_id,
        player_id, coords->x, coords->y);
    SLIST_FOREACH(node, &clients_manager->gui_clients_list, next)
    {
        client_add_request(node->client, response, TO_SEND);
    }
}
