/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** player.c
*/

#include "map/map.h"

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
