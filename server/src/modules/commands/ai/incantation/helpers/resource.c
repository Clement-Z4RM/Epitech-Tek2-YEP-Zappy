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

/**
 * @brief Check if the cell always contains the required resources
 * at the end of the incantation.
 *
 * @param incantation The incantation to check.
 * @param cell The cell to check.
 *
 * @return true if the cell contains the required resources, false otherwise.
 */
bool cell_contains_required_resources(incantation_t *incantation, cell_t *cell)
{
    for (resource_name_t resource = 0; resource < RESOURCES_COUNT; ++resource)
        if (cell->resources[resource] <
            INCANTATIONS_REQUIREMENTS[incantation->level].resources[resource] *
                incantation->nb_players)
            return false;
    return true;
}

/**
 * @brief Remove the required resources from the cell after the incantation.
 *
 * @param incantation The incantation to remove the resources for.
 * @param cell The cell where the resources will be removed.
 */
void remove_incantation_resources(incantation_t *incantation, cell_t *cell)
{
    for (resource_name_t resource = 0; resource < RESOURCES_COUNT; ++resource)
        cell->resources[resource] -=
            INCANTATIONS_REQUIREMENTS[incantation->level].resources[resource] *
            incantation->nb_players;
}
