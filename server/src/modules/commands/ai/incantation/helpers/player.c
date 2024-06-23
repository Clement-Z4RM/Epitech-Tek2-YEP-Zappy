/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** player.c
*/

#include "../incantation.h"

// TODO: doc

static bool player_have_required_resources(
    player_t *player,
    u_int8_t level
)
{
    for (resource_name_t resource = 0; resource < RESOURCES_COUNT; ++resource)
        if (player->resources[resource] <
            INCANTATIONS_REQUIREMENTS[level].resources[resource])
            return false;
    return true;
}

static bool add_player(
    incantation_t *incantation,
    ai_client_node_t *client,
    u_int8_t *players
)
{
    incantation_player_t *player;

    if (!player_have_required_resources(&client->player, incantation->level))
        return true;
    player = malloc(sizeof(incantation_player_t));
    if (!player)
        return false;
    player->player = client;
    SLIST_INSERT_HEAD(&incantation->players, player, next);
    ++*players;
    return true;
}

static bool add_team_players(
    incantation_t *incantation,
    team_node_t *team,
    u_int8_t *players,
    ai_client_node_t *requester
)
{
    ai_client_node_t *client;

    SLIST_FOREACH(client, &team->ai_clients, next)
    if (client != requester &&
        client->player.level == incantation->level &&
        !add_player(incantation, client, players))
        return false;
    return true;
}

bool add_players_to_incantation(
    incantation_t *incantation,
    ai_client_node_t *client,
    team_list_t *teams,
    u_int8_t *players
)
{
    team_node_t *team;

    if (!add_player(incantation, client, players))
        return false;
    SLIST_FOREACH(team, teams, next)
        if (!add_team_players(incantation, team, players, client))
            return false;
    return true;
}
