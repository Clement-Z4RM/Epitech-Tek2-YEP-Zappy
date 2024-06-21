/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** pex command (expulsion)
*/

#include <string.h>
#include "../gui_commands.h"

void pnw(const ai_client_node_t *ai_client, const clients_manager_t
    *clients_manager)
{
    gui_client_node_t *node = NULL;
    char *response = malloc(MAX_RESPONSE_SIZE);

    if (response)
        snprintf(
            response,
            MAX_RESPONSE_SIZE,
            "pnw #%lu %zu %zu %d %d %s\n",
            ai_client->player.id,
            ai_client->player.x,
            ai_client->player.y,
            ai_client->player.direction,
            ai_client->player.level,
            ai_client->client->team_name
        );
    SLIST_FOREACH(node, &clients_manager->gui_clients_list, next)
        if (response)
            client_add_request(node->client, response, TO_SEND);
        else
            client_add_request(node->client, strdup("ok\n"), TO_SEND);
}
