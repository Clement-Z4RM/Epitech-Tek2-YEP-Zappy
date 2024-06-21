/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** ppo.c
*/

#include <string.h>
#include "../gui_commands.h"

static bool fill_response(gui_handler_data_t *data, char *response)
{
    char *endptr = NULL;
    const uint64_t id = strtol(data->args[1], &endptr, 10);
    ai_client_node_t *ai_client;

    if (*endptr != '\0') {
        sbp(data->gui_client->client);
        return false;
    }
    ai_client = clients_manager_get_ai_by_id(
        data->updater->network->clients_manager, id
    );
    if (ai_client == NULL) {
        sbp(data->gui_client->client);
        return false;
    }
    snprintf(response, MAX_RESPONSE_SIZE, "ppo %ld %lu %lu %d\n",
             ai_client->player.id, ai_client->player.x, ai_client->player.y,
             ai_client->player.direction);
    return true;
}

void ppo(gui_handler_data_t *data)
{
    char *response = malloc(MAX_RESPONSE_SIZE);

    if (!response) {
        client_add_request(data->gui_client->client, strdup("ok\n"), TO_SEND);
        return;
    }
    if (!fill_response(data, response))
        return;
    client_add_request(data->gui_client->client, response, TO_SEND);
}
