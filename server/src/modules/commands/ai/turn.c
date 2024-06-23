/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** turn.c
*/

#include <string.h>
#include "player/player_methods.h"
#include "requests_manager/requests_manager.h"

static void right_updater(
    ai_client_node_t *client,
    UNUSED updater_t *updater,
    UNUSED void *arg
)
{
    client->client->busy = false;
    player_turn(client, PR_RIGHT);
    client_add_request(client->client, strdup("ok\n"), TO_SEND);
    ppo_event(client, updater->network->clients_manager);
}

/**
 * @brief Right command.
 * Turn the player forward 90° right.
 *
 * This command takes 7 ticks to execute.
 *
 * @param data The structure containing all needed informations.
 */
void right(ai_handler_data_t *data)
{
    command_updater_data_t updater_data = {
        data->updater->elapsed,
        7,
        data->client,
        NULL
    };

    data->client->client->busy = true;
    updater_add_command(data->updater, &updater_data, right_updater);
    log_success_turn(&data->client->player);
}

static void left_updater(
    ai_client_node_t *client,
    UNUSED updater_t *updater,
    UNUSED void *arg
)
{
    client->client->busy = false;
    player_turn(client, PR_LEFT);
    client_add_request(client->client, strdup("ok\n"), TO_SEND);
    ppo_event(client, updater->network->clients_manager);
    log_success_turn(&client->player);
}

/**
 * @brief Left command.
 * Turn the player forward 90° left.
 *
 * This command takes 7 ticks to execute.
 *
 * @param data The structure containing all needed informations.
 */
void left(ai_handler_data_t *data)
{
    command_updater_data_t updater_data = {
        data->updater->elapsed,
        7,
        data->client,
        NULL
    };

    data->client->client->busy = true;
    updater_add_command(data->updater, &updater_data, left_updater);
}
