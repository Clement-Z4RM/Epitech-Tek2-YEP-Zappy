/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** ppo.c
*/

#include "../gui_commands.h"

void ppo(gui_handler_data_t *data)
{
    char *endptr = NULL;
    uint64_t id = strtol(data->args[1], &endptr, 10);
    ai_client_node_t *ai_client = NULL;
    char response[MAX_RESPONSE_SIZE];

    if (*endptr != '\0') {
        sbp(data->gui_client->client);
        return;
    }
    ai_client = clients_manager_get_ai_by_id(data->updater
        ->network->clients_manager, id);
    if (ai_client == NULL) {
        sbp(data->gui_client->client);
        return;
    }
    snprintf(response, MAX_RESPONSE_SIZE, "ppo %ld %lu %lu %d\n", ai_client
        ->player.id, ai_client->player.x, ai_client->player.y,
        ai_client->player.direction);
}
