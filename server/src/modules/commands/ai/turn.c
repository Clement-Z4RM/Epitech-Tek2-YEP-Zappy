/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** turn.c
*/

#include <string.h>
#include "player/player_utilities.h"
#include "requests_manager/requests_manager.h"

/**
 * @brief Right command.
 * Turn the player forward 90° right.
 *
 * This command takes 7 ticks to execute. TODO: time
 *
 * @param data The structure containing all needed informations.
 */
void right(ai_handler_data_t *data)
{
    player_turn(data->client, PR_RIGHT);
    client_add_request(data->client->client, strdup("ok\n"), TO_SEND);
}

/**
 * @brief Left command.
 * Turn the player forward 90° left.
 *
 * This command takes 7 ticks to execute. TODO: time
 *
 * @param data The structure containing all needed informations.
 */
void left(ai_handler_data_t *data)
{
    player_turn(data->client, PR_LEFT);
    client_add_request(data->client->client, strdup("ok\n"), TO_SEND);
}
