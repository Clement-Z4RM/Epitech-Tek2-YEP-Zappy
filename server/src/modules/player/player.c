/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** player.c
*/

#include <stdlib.h>
#include <string.h>
#include "map/map.h"
#include "responses.h"
#include <stdio.h>

/**
 * @brief Get a random egg from a team.
 *
 * @param team The team to get the egg from.
 *
 * @return The egg, or NULL if the team has no more egg.
 */
static team_egg_t *get_random_team_egg(team_node_t *team)
{
    team_egg_t *team_egg;
    ulong egg_index;

    if (0 == team->nb_eggs)
        return NULL;
    team_egg = SLIST_FIRST(&team->eggs);
    if (!team_egg)
        return NULL;
    egg_index = random() % team->nb_eggs;
    for (ulong i = 0; i < egg_index; ++i)
        team_egg = SLIST_NEXT(team_egg, next);
    SLIST_REMOVE(&team->eggs, team_egg, team_egg_s, next);
    --team->nb_eggs;
    return team_egg;
}

/**
 * @brief Initialize the fields of player's structure
 * and place it on the map at a random egg position from its team.
 *
 * @param client The client related to the player to initialize.
 * @param map The map where to place it.
 * @param team The player's teams (to get the egg).
 * @param id The id of the player.
 *
 * @return true if the player has been initialized,
 * false otherwise (no egg for its team).
 */
bool initialize_player(
    ai_client_node_t *client,
    map_t *map,
    team_node_t *team,
    u_int64_t id
)
{
    team_egg_t *team_egg = get_random_team_egg(team);
    cell_t *cell;

    if (!team_egg)
        return false;
    cell = &map->cells[team_egg->egg->y][team_egg->egg->x];
    client->player.life_span = 1260;
    SLIST_REMOVE(&cell->eggs, team_egg->egg, egg_s, next);
    client->player.x = team_egg->egg->x;
    client->player.y = team_egg->egg->y;
    free(team_egg->egg);
    free(team_egg);
    client->player.direction = random() % 4 + 1;
    memset(client->player.resources, 0, sizeof(client->player.resources));
    client->player.id = id;
    client->player.level = 1;
    SLIST_INSERT_HEAD(&cell->players, client, next);
    return true;
}

/**
 * @brief Move the player forward depending on its direction.
 * Also update the player's position on the map.
 *
 * Client structure is sent to update the player's position on the map.
 *
 * @param client The client related to the player to move.
 * @param map The map where the player is.
 */
void player_go_forward(ai_client_node_t *client, map_t *map)
{
    player_t *player = &client->player;
    u_int64_t x = player->x;
    u_int64_t y = player->y;

    switch (player->direction) {
        case PD_UP:
            player->y = (player->y - 1) % map->height;
            break;
        case PD_RIGHT:
            player->x = (player->x + 1) % map->width;
            break;
        case PD_DOWN:
            player->y = (player->y + 1) % map->height;
            break;
        case PD_LEFT:
            player->x = (player->x - 1) % map->width;
            break;
    }
    SLIST_REMOVE(&map->cells[y][x].players, client, ai_client_node_s, next);
    SLIST_INSERT_HEAD(&map->cells[player->y][player->x].players, client, next);
}

/**
 * @brief Turn the player to the left or to the right.
 *
 * @param client The client related to the player to turn.
 * @param rotation The rotation to apply to the player (left or right).
 */
void player_turn(ai_client_node_t *client, player_rotation_t rotation)
{
    player_t *player = &client->player;

    player->direction = (player->direction + rotation) % 4;
    if (0 == player->direction)
        player->direction = PD_LEFT;
}

/**
 * @brief Take a resource from the map and give it to the player.
 *
 * @param client The client related to the player to give the resource to.
 * @param map The map where the player and the resource is.
 * @param resource The resource to take.
 *
 * @return true if the resource has been taken,
 * false otherwise (no resource at the player's position).
 */
bool player_take_resource(
    ai_client_node_t *client,
    map_t *map,
    resource_name_t resource
)
{
    u_int64_t x = client->player.x;
    u_int64_t y = client->player.y;

    if (0 == map->cells[y][x].resources[resource])
        return false;
    --map->cells[y][x].resources[resource];
    if (RN_FOOD == resource)
        client->player.life_span += 126;
    else
        ++client->player.resources[resource];
    return true;
}

/**
 * @brief Drop a resource on the map from the player's inventory.
 *
 * @param client The client related to the player to take the resource from.
 * @param map The map where the player is.
 * @param resource The resource to drop.
 *
 * @return true if the resource has been dropped,
 * false otherwise (trying to drop a resource the player doesn't have or food).
 */
bool player_drop_resource(
    ai_client_node_t *client,
    map_t *map,
    resource_name_t resource
)
{
    u_int64_t x = client->player.x;
    u_int64_t y = client->player.y;

    if (RN_FOOD == resource)
        return false;
    if (0 == client->player.resources[resource])
        return false;
    --client->player.resources[resource];
    ++map->cells[y][x].resources[resource];
    return true;
}
