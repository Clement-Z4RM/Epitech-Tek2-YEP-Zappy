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
    UNUSED char *arg
)
{
    player_turn(client, PR_RIGHT);
    client_add_request(client->client, strdup("ok\n"), TO_SEND);
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

    updater_add_command(data->updater, &updater_data, right_updater);
}

static void left_updater(
    ai_client_node_t *client,
    UNUSED updater_t *updater,
    UNUSED char *arg
)
{
    player_turn(client, PR_LEFT);
    client_add_request(client->client, strdup("ok\n"), TO_SEND);
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

    updater_add_command(data->updater, &updater_data, left_updater);
}
