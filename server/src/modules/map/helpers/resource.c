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

//region Compute resource quantities
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
    float quantity;

    map->resources.quantities[RESOURCES_COUNT] = 0;
    for (resource_name_t resource = 0; resource < RESOURCES_COUNT; ++resource) {
        quantity = (float)map_area * RESOURCE_DENSITIES[resource];
        if (quantity < 1)
            quantity = 1;
        map->resources.quantities[resource] = (size_t)quantity;
        map->resources.quantities[RESOURCES_COUNT] += (size_t)quantity;
    }
}
//endregion

//region Resources generation
/**
 * @brief Generate a resource on the map, and store it in a random cell.
 *
 * @param map The map where the resource is generated.
 * @param resource The resource to generate.
 *
 * @return true if the resource was successfully generated,
 * false otherwise (allocation error).
 */
static bool generate_resource(map_t *map, resource_name_t resource)
{
    size_t x = random() % map->x;
    size_t y = random() % map->y;
    resource_t *new_resource = malloc(sizeof(resource_t));

    if (!new_resource) {
        perror("malloc");
        return false;
    }
    new_resource->name = resource;
    new_resource->type = (resource == RN_FOOD ? RT_FOOD : RT_STONE);
    SLIST_INSERT_HEAD(&map->cells[y][x].resources, new_resource, next);
    return true;
}

/**
 * @brief Generate resources (stones and foods) on the map
 * depending on previously computed quantity of each resource.
 * This function should be called at startup
 * and every 20 time units (once at least an AI is connected).
 *
 * @param map The map where the resources are generated.
 *
 * @return true if the resources were successfully generated,
 * false otherwise (allocation error).
 */
static bool generate_resources(map_t *map)
{
    for (resource_name_t resource = 0; resource <= RESOURCES_COUNT; ++resource)
        for (size_t i = 0; i < map->resources.quantities[resource]; ++i)
            if (!generate_resource(map, resource)) {
                map->destroy(map);
                return false;
            }
    return true;
}
//endregion

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
