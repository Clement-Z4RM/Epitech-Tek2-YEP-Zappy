/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** resource.c
*/

#include "../incantation.h"

/**
 * @brief Drop the required resources for the incantation
 * from the players' inventory on the map.
 *
 * @param incantation The incantation where the players are.
 * @param map The map where the resources will be dropped.
 */
void drop_resources(incantation_t *incantation, map_t *map)
{
    for (
        incantation_player_t *player = SLIST_FIRST(&incantation->players);
        player;
        player = SLIST_NEXT(player, next)
    ) {
        for (resource_name_t r = 0; r < RESOURCES_COUNT; ++r) {
            map->cells[incantation->y][incantation->x].resources[r] +=
                INCANTATIONS_REQUIREMENTS[incantation->level].resources[r];
            player->player->player.resources[r] -=
                INCANTATIONS_REQUIREMENTS[incantation->level].resources[r];
        }
    }
}
