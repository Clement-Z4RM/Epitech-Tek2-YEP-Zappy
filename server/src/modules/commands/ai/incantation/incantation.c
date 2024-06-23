/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** incantation.c
*/

#include <string.h>
#include "incantation.h"

void win_condition(int *winner_count, updater_t *updater, team_node_t
    *current_team, ai_client_node_t *current_ai)
{
    if (current_ai->player.level == 8) {
        (*winner_count)++;
        if (*winner_count == 6) {
            LOG_SUCCESS("Team %s won the game\n", current_team->name);
            updater->end_of_game = true;
            updater->start = 0;
            updater->network->clients_manager->is_game_started = false;
            seg(current_team->name, updater->network->clients_manager);
        }
    }
}

static void check_for_win(updater_t *updater)
{
    team_node_t *current_team = NULL;
    ai_client_node_t *current_ai = NULL;
    int winner_count = 0;

    SLIST_FOREACH(current_team,
        &updater->network->clients_manager->team_list, next) {
        SLIST_FOREACH(current_ai, &current_team->ai_clients, next) {
            win_condition(&winner_count, updater, current_team, current_ai);
        }
        winner_count = 0;
    }
}

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
    char response[20];
    bool result = 1;

    client->client->busy = false;
    if (!cell_contains_required_resources(incantation->level, cell)) {
        add_request_to_all_players(incantation, "ko\n");
        result = 0;
    } else {
        remove_incantation_resources(incantation->level, cell);
        elevate_players(incantation);
        snprintf(response, 20, "Current level: %d\n", incantation->level + 1);
        add_request_to_all_players(incantation, response);
    }
    pie(incantation->x, incantation->y, result,
        updater->network->clients_manager);
    incantation->updater.command_updater = NULL;
    incantation->destroy(incantation);
    check_for_win(updater);
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
        data->client->player.id,
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
