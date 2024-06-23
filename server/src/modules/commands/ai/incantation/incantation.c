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

static void elevate_players(incantation_t *incantation)
{
    incantation_player_t *player;

    SLIST_FOREACH(player, &incantation->players, next)
        ++player->player->player.level;
}

static void incantation_updater(
    ai_client_node_t *client,
    updater_t *updater,
    void *arg
)
{
    incantation_t *incantation = (incantation_t *)arg;
    cell_t *cell = &updater->map->cells[incantation->y][incantation->x];
    char response[18];

    client->client->busy = false;
    if (!cell_contains_required_resources(incantation, cell))
        add_request_to_all_players(incantation, "ko\n");
    else {
        remove_incantation_resources(incantation, cell);
        elevate_players(incantation);
        snprintf(response, 18, "Current level: %d\n", incantation->level + 1);
        add_request_to_all_players(incantation, response);
    }
    incantation->updater.command_updater = NULL;
    incantation->destroy(incantation);
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
