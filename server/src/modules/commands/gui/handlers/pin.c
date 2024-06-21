/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** pin.c
*/

#include <string.h>
#include "../gui_commands.h"

static void fill_response(char *response, ai_client_node_t *ai_client)
{
    uint64_t q0 = ai_client->player.resources[RN_FOOD];
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

void pin(gui_handler_data_t *data)
{
    char *response = malloc(MAX_RESPONSE_SIZE);
    char *endptr = NULL;
    const uint64_t id = strtol(data->args[1], &endptr, 10);
    ai_client_node_t *ai_client = clients_manager_get_ai_by_id(
        data->updater->network->clients_manager,
        id
    );

    if (!response) {
        client_add_request(data->gui_client->client, strdup("ko\n"), TO_SEND);
        return;
    }
    fill_response(response, ai_client);
    client_add_request(data->gui_client->client, response, TO_SEND);
}
