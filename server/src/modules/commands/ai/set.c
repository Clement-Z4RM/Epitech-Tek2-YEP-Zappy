/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** set.c
*/

#include <string.h>
#include "player/player_methods.h"
#include "requests_manager/requests_manager.h"

static void set_updater(
    ai_client_node_t *client,
    updater_t *updater,
    void *arg
)
{
    resource_name_t resource = 0;
    bool success = false;

    client->client->busy = false;
    if (!arg) {
        client_add_request(client->client, strdup("ko\n"), TO_SEND);
        return;
    }
    for (; resource < RESOURCES_COUNT; ++resource)
        if (RESOURCE_NAMES[resource] &&
            !strcmp(RESOURCE_NAMES[resource], (char *)arg)) {
            success = player_drop_resource(client, updater->map, resource);
            break;
        }
    if (success)
        client_add_request(client->client, strdup("ok\n"), TO_SEND);
    else
        client_add_request(client->client, strdup("ko\n"), TO_SEND);
    free((char *)arg);
}

/**
 * @brief Set command.
 * Set a resource down on the map from the player's inventory.
 *
 * This command takes 7 ticks to execute.
 *
 * @param data The structure containing all needed informations.
 */
void set(ai_handler_data_t *data)
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
    updater_data.arg = (void *)strdup(data->args[1]);
    data->client->client->busy = true;
    updater_add_command(data->updater, &updater_data, set_updater);
}
