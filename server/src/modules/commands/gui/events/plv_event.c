/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** pex command (expulsion)
*/

#include <string.h>
#include "../gui_commands.h"

void plv_event(
    const player_t *player,
    const clients_manager_t *clients_manager
)
{
    char response[MAX_RESPONSE_SIZE];
    const gui_client_node_t *node = NULL;

    snprintf(
        response,
        MAX_RESPONSE_SIZE,
        "plv %lu %d\n", player->id,
        player->level
    );
    SLIST_FOREACH(node, &clients_manager->gui_clients_list, next)
        client_add_request(node->client, strdup(response), TO_SEND);
}
