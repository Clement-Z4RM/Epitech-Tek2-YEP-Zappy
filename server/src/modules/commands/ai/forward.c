/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** forward.c
*/

#include <string.h>
#include "player/player_methods.h"
#include "requests_manager/requests_manager.h"

static void forward_updater(
    ai_client_node_t *client,
    updater_t *updater,
    UNUSED void *arg
)
{
    client->client->busy = false;
    player_go_forward(client, updater->map);
    client_add_request(client->client, strdup("ok\n"), TO_SEND);
    ppo_event(client, updater->network->clients_manager);
    log_success_forward(&client->player);
}

/**
 * @brief Forward command.
 * Move the player forward of one tile in the direction he is facing.
 *
 * This command takes 7 ticks to execute.
 *
 * @param data The structure containing all needed informations.
 */
void forward(ai_handler_data_t *data)
{
    command_updater_data_t updater_data = {
        data->updater->elapsed,
        7,
        data->client,
        data->client->player.id,
        NULL
    };

    data->client->client->busy = true;
    updater_add_command(data->updater, &updater_data, forward_updater);
}
