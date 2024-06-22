/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** take.c
*/

#include <string.h>
#include "player/player_methods.h"
#include "requests_manager/requests_manager.h"

static void take_updater(
    ai_client_node_t *client,
    updater_t *updater,
    char *arg
)
{
    resource_name_t resource = 0;
    bool success = false;

    if (!arg) {
        client_add_request(client->client, strdup("ko\n"), TO_SEND);
        return;
    }
    for (; resource < RESOURCES_COUNT; ++resource)
        if (RESOURCE_NAMES[resource] &&
            !strcmp(RESOURCE_NAMES[resource], arg)) {
            success = player_take_resource(client, updater->map, resource);
            break;
        }
    if (success) {
        client_add_request(client->client, strdup("ok\n"), TO_SEND);
        pgt(client->player.id, resource, updater->network->clients_manager);
    } else
        client_add_request(client->client, strdup("ko\n"), TO_SEND);
    free(arg);
}

/**
 * @brief Take command.
 * Take a resource from the map and give it to the player.
 *
 * This command takes 7 ticks to execute.
 *
 * @param data The structure containing all needed informations.
 */
void take(ai_handler_data_t *data)
{
    command_updater_data_t updater_data = {
        .executed_at = data->updater->elapsed,
        .time = 7,
        .client = data->client
    };

    if (!data->args[1]) {
        client_add_request(data->client->client, strdup("ko\n"), TO_SEND);
        return;
    }
    updater_data.arg = strdup(data->args[1]);
    updater_add_command(data->updater, &updater_data, take_updater);
}
