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

static bool add_team_players_to_incantation(
    incantation_t *incantation,
    team_node_t *team,
    u_int8_t *players
)
{
    ai_client_node_t *client;
    incantation_player_t *player;

    SLIST_FOREACH(client, &team->ai_clients, next)
        if (client->player.level == incantation->level) {
            player = malloc(sizeof(incantation_player_t));
            if (!player)
                return false;
            player->player = client;
            SLIST_INSERT_HEAD(&incantation->players, player, next);
            ++*players;
        }
    return true;
}

static incantation_t *create_incantation(u_int8_t level, team_list_t *teams)
{
    incantation_t *incantation = malloc(sizeof(incantation_t));
    u_int8_t players = 0;
    team_node_t *team;

    if (!incantation)
        return NULL;
    incantation->level = level;
    SLIST_INIT(&incantation->players);
    SLIST_FOREACH(team, teams, next)
        if (!add_team_players_to_incantation(incantation, team, &players)) {
            incantation_destructor(incantation);
            return NULL;
        }
    if (players < INCANTATIONS_REQUIREMENTS[level].players) {
        incantation_destructor(incantation);
        return NULL;
    }
    return incantation;
}

incantation_t *initiate_incantation(ai_handler_data_t *data)
{
    u_int8_t level = data->client->player.level;
    const incantation_requirements_t *requirements;
    incantation_t *incantation;

    if (level == 0 || level > 7)
        return NULL;
    requirements = &INCANTATIONS_REQUIREMENTS[level];
    incantation = create_incantation(level, &data->clients_manager->team_list);
    if (!incantation)
        return NULL;
    incantation->destroy = incantation_destructor;
    return incantation;
}
