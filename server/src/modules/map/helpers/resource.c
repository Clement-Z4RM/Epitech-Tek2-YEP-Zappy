/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** resource.c
*/

#include <stdlib.h>
#include <stdio.h>
#include "map/map.h"
#include "resource/resource.h"

/**
 * @brief Compute the quantity for each resource on the map
 * depending on the width and height of it and the resource density,
 * and store them in the map.
 * If the quantity is less than 1, it is set to 1 given that there must be
 * at least one of each resource on the map.
 *
 * @param map The map where the computation is done
 * and the quantities are stored.
 */
static void compute_resource_quantities(map_t *map)
{
    size_t map_area = map->width * map->height;
    resource_name_t resource = 0;
    float quantity;

    map->resources.quantities[RESOURCES_COUNT] = 0;
    for (; resource < RESOURCES_COUNT; ++resource) {
        quantity = (float)map_area * RESOURCES[resource].density;
        if (quantity < 1)
            quantity = 1;
        map->resources.quantities[resource] = (size_t)quantity;
        map->resources.quantities[RESOURCES_COUNT] += (size_t)quantity;
    }
}

/**
 * @brief Generate resources (stones and foods) on the map
 * depending on previously computed quantity of each resource.
 * This function should be called at startup
 * and every 20 time units (once at least an AI is connected).
 *
 * @param map The map where the resources are generated.
 */
static void generate_resources(map_t *map)
{
    size_t x;
    size_t y;

    for (resource_name_t resource = 0; resource < RESOURCES_COUNT; ++resource)
        for (size_t i = 0; i < map->resources.quantities[resource]; ++i) {
            x = random() % map->x;
            y = random() % map->y;
            ++map->cells[y][x].resources[resource];
        }
}

/**
 * @brief Initialize the resources helper in the map structure.
 * Compute the quantities for each resource (only used in resources generator).
 * Also set the resources generation function and call it a first time.
 *
 * @param map The map where the resources are initialized.
 */
void initialize_resources(map_t *map)
{
    compute_resource_quantities(map);
    map->resources.generate = generate_resources;
    map->resources.generate(map);
}
