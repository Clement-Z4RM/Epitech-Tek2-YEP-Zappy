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
    const uint64_t id = strtol(data->args[1], &endptr, 10);
    ai_client_node_t *ai_client = NULL;
    char response[MAX_RESPONSE_SIZE];

    if (*endptr != '\0')
        return sbp(data->gui_client->client);
    ai_client = clients_manager_get_ai_by_id(data->updater
        ->network->clients_manager, id);
    if (ai_client == NULL)
        return sbp(data->gui_client->client);
    snprintf(response, MAX_RESPONSE_SIZE, "ppo %ld %lu %lu %d\n", ai_client
        ->player.id, ai_client->player.x, ai_client->player.y,
        ai_client->player.direction);
    client_add_request(data->gui_client->client, response, TO_SEND);
}
