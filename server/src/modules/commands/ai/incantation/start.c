/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** initiate.c
*/

#include "incantation.h"

/**
 * @brief Incantation structure destructor
 *
 * @param incantation The incantation to destroy
 */
static void incantation_destructor(incantation_t *incantation)
{
    incantation_player_t *tmp;

    while (!SLIST_EMPTY(&incantation->players)) {
        tmp = SLIST_FIRST(&incantation->players);
        SLIST_REMOVE_HEAD(&incantation->players, next);
        free(tmp);
    }
    if (incantation->updater.command_updater) {
        CIRCLEQ_REMOVE(
            incantation->updater.command_updaters,
            incantation->updater.command_updater,
            next
        );
        free(incantation->updater.command_updater);
    }
    free(incantation);
}

/**
 * @brief Allocate the incantation and add the players to it.
 *
 * @param client The client initiating the incantation.
 * @param teams The teams list.
 *
 * @return The incantation if it was successfully created,
 * NULL otherwise (not enough players of the required level,
 * not enough resources, or allocation error).
 */
static incantation_t *create_incantation(
    ai_client_node_t *client,
    team_list_t *teams
)
{
    incantation_t *incantation = malloc(sizeof(incantation_t));

    if (!incantation)
        return NULL;
    incantation->level = client->player.level;
    SLIST_INIT(&incantation->players);
    incantation->nb_players = 0;
    if (!add_players_to_incantation(incantation, client, teams)) {
        incantation_destructor(incantation);
        return NULL;
    }
    if (incantation->nb_players <
        INCANTATIONS_REQUIREMENTS[client->player.level].players) {
        incantation_destructor(incantation);
        return NULL;
    }
    return incantation;
}

/**
 * @brief Start (initiate) an incantation.
 *
 * @param data The structure containing all needed informations.
 *
 * @return The incantation if it was successfully created,
 * NULL otherwise (cf. create_incantation for possible errors).
 */
incantation_t *start_incantation(ai_handler_data_t *data)
{
    u_int8_t level = data->client->player.level;
    incantation_t *incantation;

    if (level == 0 || level > 7)
        return NULL;
    incantation = create_incantation(
        data->client,
        &data->clients_manager->team_list
    );
    if (!incantation)
        return NULL;
    drop_resources(incantation, data->updater->map);
    incantation->destroy = incantation_destructor;
    return incantation;
}
