/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** incantation.c
*/

#include <string.h>
#include "incantation.h"

static void add_request_to_all_players(
    incantation_t *incantation,
    const char *request
)
{
    incantation_player_t *player;

    SLIST_FOREACH(player, &incantation->players, next)
        client_add_request(
            player->player->client,
            strdup(request),
            TO_SEND
        );
}

static void incantation_updater(
    ai_client_node_t *client,
    UNUSED updater_t *updater,
    UNUSED char *arg
)
{
    client->client->busy = false;
}

/**
 * @brief Incantation command.
 * Start an incantation (elevation ritual).
 *
 * This command takes 300 ticks to execute.
 *
 * @param data The structure containing all needed informations.
 */
void incantation(ai_handler_data_t *data)
{
    command_updater_data_t updater_data = {
        data->updater->elapsed,
        300,
        data->client,
        NULL
    };
    incantation_t *incantation = start_incantation(data);

    if (!incantation) {
        client_add_request(data->client->client, strdup("ko\n"), TO_SEND);
        return;
    }
    add_request_to_all_players(incantation, "Elevation underway\n");
    updater_data.arg = (void *)incantation;
    data->client->client->busy = true;
    updater_add_command(data->updater, &updater_data, incantation_updater);
}
