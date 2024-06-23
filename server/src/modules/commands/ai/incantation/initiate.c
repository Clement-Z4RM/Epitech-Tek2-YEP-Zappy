/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** initiate.c
*/

#include "incantation.h"

// TODO: doc

static void incantation_destructor(incantation_t *incantation)
{
    incantation_player_t *tmp;

    while (!SLIST_EMPTY(&incantation->players)) {
        tmp = SLIST_FIRST(&incantation->players);
        SLIST_REMOVE_HEAD(&incantation->players, next);
        free(tmp);
    }
    CIRCLEQ_REMOVE(
        incantation->updater.command_updaters,
        incantation->updater.command_updater,
        next
    );
    free(incantation->updater.command_updater);
    free(incantation);
}

static incantation_t *create_incantation(
    ai_client_node_t *client,
    team_list_t *teams
)
{
    incantation_t *incantation = malloc(sizeof(incantation_t));
    u_int8_t players = 0;

    if (!incantation)
        return NULL;
    incantation->level = client->player.level;
    SLIST_INIT(&incantation->players);
    if (!add_players_to_incantation(incantation, client, teams, &players)) {
        incantation_destructor(incantation);
        return NULL;
    }
    if (players < INCANTATIONS_REQUIREMENTS[client->player.level].players) {
        incantation_destructor(incantation);
        return NULL;
    }
    return incantation;
}

incantation_t *initiate_incantation(ai_handler_data_t *data)
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
