/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** take.c
*/

#include <string.h>
#include "player/player_methods.h"
#include "requests_manager/requests_manager.h"

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
    resource_name_t resource = 0;
    bool success = false;

    for (; resource < RESOURCES_COUNT; ++resource)
        if (RESOURCE_NAMES[resource] &&
            !strcmp(RESOURCE_NAMES[resource], data->args[1])) {
            success = player_take_resource(
                data->client,
                data->updater->map,
                resource
            );
            break;
        }
    if (success)
        client_add_request(data->client->client, strdup("ok\n"), TO_SEND);
    else
        client_add_request(data->client->client, strdup("ko\n"), TO_SEND);
}
