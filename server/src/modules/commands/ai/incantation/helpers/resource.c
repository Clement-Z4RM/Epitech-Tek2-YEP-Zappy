/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** resource.c
*/

#include "../incantation.h"

/**
 * @brief Check if the cell contains the required resources
 * for the current level of incantation.
 *
 * @param level The level of the incantation.
 * @param cell The cell to check.
 *
 * @return true if the cell contains the required resources, false otherwise.
 */
bool cell_contains_required_resources(u_int8_t level, cell_t *cell)
{
    for (resource_name_t resource = 0; resource < RESOURCES_COUNT; ++resource)
        if (cell->resources[resource] <
            INCANTATIONS_REQUIREMENTS[level].resources[resource])
            return false;
    return true;
}

/**
 * @brief Remove the required resources from the cell after the incantation.
 *
 * @param level The level of the incantation.
 * @param cell The cell where the resources will be removed.
 */
void remove_incantation_resources(u_int8_t level, cell_t *cell)
{
    for (resource_name_t resource = 0; resource < RESOURCES_COUNT; ++resource)
        cell->resources[resource] -=
            INCANTATIONS_REQUIREMENTS[level].resources[resource];
}
