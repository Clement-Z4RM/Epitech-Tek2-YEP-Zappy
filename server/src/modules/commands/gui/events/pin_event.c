/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** pin event
*/

#include "../gui_commands.h"
#include <string.h>

static void fill_response(char *response, ai_client_node_t *ai_client)
{
    uint64_t q0 = (uint64_t)ai_client->player.life_span / 126;
    uint64_t q1 = ai_client->player.resources[RN_LINEMATE];
    uint64_t q2 = ai_client->player.resources[RN_DERAUMERE];
    uint64_t q3 = ai_client->player.resources[RN_SIBUR];
    uint64_t q4 = ai_client->player.resources[RN_MENDIANE];
    uint64_t q5 = ai_client->player.resources[RN_PHIRAS];
    uint64_t q6 = ai_client->player.resources[RN_THYSTAME];

    snprintf(response, MAX_RESPONSE_SIZE,
        "pin %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu\n",
        ai_client->player.id,
        ai_client->player.x,
        ai_client->player.y,
        q0, q1, q2, q3, q4, q5, q6
    );
}

void pin_event(uint64_t id, clients_manager_t *clients_manager)
{
    char response[MAX_RESPONSE_SIZE];
    gui_client_node_t *gui_client = NULL;
    ai_client_node_t *ai_client = clients_manager_get_ai_by_id(
        clients_manager,
        id
    );

    fill_response(response, ai_client);
    SLIST_FOREACH(gui_client, &clients_manager->gui_clients_list, next) {
        client_add_request(gui_client->client, strdup(response), TO_SEND);
    }
}
