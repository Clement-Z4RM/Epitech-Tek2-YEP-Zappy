/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** ppo event
*/

#include "../gui_commands.h"
#include <string.h>

void ppo_event(ai_client_node_t *ai_client, clients_manager_t *client_manager)
{
    char response[MAX_RESPONSE_SIZE];
    gui_client_node_t *gui_client;

    snprintf(response, MAX_RESPONSE_SIZE, "ppo %ld %lu %lu %d\n",
        ai_client->player.id, ai_client->player.x, ai_client->player.y,
        ai_client->player.direction);
    SLIST_FOREACH(gui_client, &client_manager->gui_clients_list, next)
        client_add_request(gui_client->client, strdup(response), TO_SEND);
}
