/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** plv handler
*/

#include "../gui_commands.h"
#include "requests_manager/requests_manager.h"
#include <string.h>

void plv(gui_handler_data_t *data)
{
    char *response = malloc(MAX_RESPONSE_SIZE);
    char *endptr = NULL;
    uint64_t player_id = strtol(data->args[1], &endptr, 10);
    ai_client_node_t *ai_client = NULL;

    if (!response) {
        client_add_request(data->gui_client->client, strdup("ko\n"), TO_SEND);
        return;
    }
    if (endptr == data->args[1]) {
        sbp(data->gui_client->client);
        return;
    }
    ai_client = clients_manager_get_ai_by_id(
        data->updater->network->clients_manager, player_id);
    if (!ai_client) {
        sbp(data->gui_client->client);
        return;
    }
    snprintf(response, MAX_RESPONSE_SIZE, "plv %lu %d\n",
        ai_client->player.id, ai_client->player.level);
    client_add_request(data->gui_client->client, response, TO_SEND);
}
