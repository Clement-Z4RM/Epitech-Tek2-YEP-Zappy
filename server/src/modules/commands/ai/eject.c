/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** eject.c
*/

#include <string.h>
#include "requests_manager/requests_manager.h"
#include "incantation/incantation.h"

static team_egg_t *get_egg_in_team(egg_t *egg, team_node_t *team)
{
    team_egg_t *team_egg;

    SLIST_FOREACH(team_egg, &team->eggs, next)
        if (team_egg->egg == egg)
            return team_egg;
    return NULL;
}

static team_egg_t *get_team_egg(
    egg_t *egg,
    team_list_t *teams,
    team_node_t **team
)
{
    team_egg_t *team_egg;

    SLIST_FOREACH(*team, teams, next) {
        team_egg = get_egg_in_team(egg, *team);
        if (team_egg)
            return team_egg;
    }
    return NULL;
}

static void destroy_egg(egg_t *egg, updater_t *updater)
{
    team_node_t *team = NULL;
    team_egg_t *team_egg = get_team_egg(
        egg,
        &updater->network->clients_manager->team_list,
        &team
    );

    if (team_egg)
        SLIST_REMOVE(&team->eggs, team_egg, team_egg_s, next);
    SLIST_REMOVE(&updater->map->cells[egg->y][egg->x].eggs, egg, egg_s, next);
    free(team_egg);
    free(egg);
}

static void eject_updater(
    ai_client_node_t *client,
    updater_t *updater,
    UNUSED void *arg
)
{
    cell_t *cell = &updater->map->cells[client->player.y][client->player.x];
    incantations_t *incantations =
        &updater->network->clients_manager->incantations;
    incantation_t *incantation;
    ai_client_node_t *player;
    egg_t *egg;

    client->client->busy = false;
    SLIST_FOREACH(incantation, incantations, next)
        if (incantation->x == client->player.x &&
            incantation->y == client->player.y) {
            cancel_incantation(incantation);
        }
    SLIST_FOREACH(egg, &cell->eggs, next)
        destroy_egg(egg, updater);
    SLIST_FOREACH(player, &cell->players, next) {
        // TODO: eject player
    }
}

/**
 * @brief Check if there is nothing to eject (neither player nor egg).
 *
 * @param data The structure containing all needed informations.
 *
 * @return true if there is nothing to eject, false otherwise.
 */
static bool nothing_to_eject(ai_handler_data_t *data)
{
    cell_t *cell = &data->updater->map->cells
        [data->client->player.y][data->client->player.x];

    return SLIST_EMPTY(&cell->players) && SLIST_EMPTY(&cell->eggs);
}

/**
 * @brief Eject command.
 * Eject all other players from a shared unit of terrain by pushing them
 * in the direction it is looking,
 * also destroying eggs and cancelling incantations.
 *
 * This command takes 7 ticks to execute.
 *
 * @param data The structure containing all needed informations.
 */
void eject(ai_handler_data_t *data)
{
    command_updater_data_t updater_data = {
        data->updater->elapsed,
        7,
        data->client,
        NULL
    };

    if (nothing_to_eject(data)) {
        client_add_request(data->client->client, strdup("ko\n"), TO_SEND);
        return;
    }
    data->client->client->busy = true;
    updater_add_command(data->updater, &updater_data, eject_updater);
}
