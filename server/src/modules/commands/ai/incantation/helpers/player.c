/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** player.c
*/

#include "../incantation.h"

/**
 * @brief Check if the player have the required resources
 * for the current level of incantation.
 *
 * @param player The player to check resources.
 * @param level The level of the incantation.
 *
 * @return true if the player have the required resources, false otherwise.
 */
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

/**
 * @brief Add a player to the incantation.
 * If the player haven't the required resources for the incantation,
 * it will not be added.
 *
 * @param incantation The incantation to add the player.
 * @param client The client to add to the incantation.
 *
 * @return
 *  - true if the player was added to the incantation,
 *  - true if the player haven't the required resources (not added),
 *  - false if an allocation error occurred.
 */
static bool add_player(incantation_t *incantation, ai_client_node_t *client)
{
    incantation_player_t *player;

    if (!player_have_required_resources(&client->player, incantation->level))
        return true;
    player = malloc(sizeof(incantation_player_t));
    if (!player)
        return false;
    player->player = client;
    SLIST_INSERT_HEAD(&incantation->players, player, next);
    ++incantation->nb_players;
    return true;
}

/**
 * @brief Add all the eligible players (with required level and resources)
 * of a team to the incantation.
 *
 * @param incantation The incantation to add the players.
 * @param team The team to add the players.
 * @param requester The client that requested the incantation.
 * If the requester is found in the team, it will not be added,
 * because it was already added.
 *
 * @return true if all the eligible players were added,
 * false otherwise (allocation error).
 */
static bool add_team_players(
    incantation_t *incantation,
    team_node_t *team,
    ai_client_node_t *requester
)
{
    ai_client_node_t *client;

    SLIST_FOREACH(client, &team->ai_clients, next)
    if (client != requester && client->player.level == incantation->level &&
        !add_player(incantation, client))
        return false;
    return true;
}

/**
 * @brief Add all the eligible players (with required level and resources)
 * to the incantation.
 *
 * @param incantation The incantation to add the players.
 * @param client The client that requested the incantation.
 * @param teams The list of teams to add the players.
 *
 * @return true if all the eligible players were added,
 * false otherwise (allocation error).
 */
bool add_players_to_incantation(
    incantation_t *incantation,
    ai_client_node_t *client,
    team_list_t *teams
)
{
    team_node_t *team;

    if (!add_player(incantation, client))
        return false;
    SLIST_FOREACH(team, teams, next)
        if (!add_team_players(incantation, team, client))
            return false;
    return true;
}
