/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** pex command (expulsion)
*/

#include "../gui_commands.h"

void pnw(ai_client_node_t *ai_client, client_manager_t *client_manager)
{
    gui_client_node_t *node = NULL;
    player_t *player = &ai_client->player;
    char response[MAX_RESPONSE_SIZE];

    snprintf(
        response,
        MAX_RESPONSE_SIZE,
        "pnw #%lu %zu %zu %d %d %s\n",
        player->id, player->x, player->y, player->direction,
        player->level, ai_client->client->team_name
    );
    SLIST_FOREACH(node, &client_manager->gui_clients_list, next)
    {
        client_add_request(node->client, response, TO_SEND);
    }
}
