/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** compute_quantities.c
*/

#include "resource/resource.h"

/**
 * @brief Compute the quantity for each resource on the map
 * depending on the width and height of it and the resource density,
 * and store them in the map.
 *
 * @param map The map where the computation is done
 * and the quantities are stored.
 */
void compute_resource_quantities(map_t *map)
{
    size_t map_area = map->width * map->height;
    float quantity;

    for (uint resource = 0; resource < RESOURCES_COUNT; ++resource) {
        quantity = (float)map_area * RESOURCE_DENSITIES[resource];
        map->resource_quantities[resource] = (size_t)quantity;
    }
}
