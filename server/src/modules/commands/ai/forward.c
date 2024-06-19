/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** forward.c
*/

#include <string.h>
#include "player/player_methods.h"
#include "requests_manager/requests_manager.h"

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
    player_go_forward(data->client, data->map);
    client_add_request(data->client->client, strdup("ok\n"), TO_SEND);
}
