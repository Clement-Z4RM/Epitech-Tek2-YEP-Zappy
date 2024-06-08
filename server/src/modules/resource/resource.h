/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** resource.h
*/

#ifndef ZAPPY_SERVER_RESOURCE_H_
    #define ZAPPY_SERVER_RESOURCE_H_

    #include <sys/queue.h>
    #include "map/map.h"

/**
 * @brief The type of a resource
 */
typedef enum resource_type_e {
    RT_FOOD,
    RT_STONE
} resource_type_t;

/**
 * @brief The name of a resource
 */
typedef enum resource_name_e {
    RN_FOOD,
    RN_LINEMATE,
    RN_DERAUMERE,
    RN_SIBUR,
    RN_MENDIANE,
    RN_PHIRAS,
    RN_THYSTAME,
    RESOURCES_COUNT
} resource_name_t;

/**
 * @brief Resource structure
 */
typedef struct resource_s {
    /** @brief The type of the resource */
    resource_type_t type;
    /** @brief The name of the resource */
    resource_name_t name;
    /** @brief The next resource in the list */
    SLIST_ENTRY(resource_s) next;
} resource_t;

/**
 * @brief Resources list
 */
SLIST_HEAD(resources_s, resource_s);
typedef struct resources_s resources_t;

/**
 * @brief The density of each resource
 */
static const float RESOURCE_DENSITIES[] = {
    [RN_FOOD] = 0.5f,
    [RN_LINEMATE] = 0.3f,
    [RN_DERAUMERE] = 0.15f,
    [RN_SIBUR] = 0.1f,
    [RN_MENDIANE] = 0.1f,
    [RN_PHIRAS] = 0.08f,
    [RN_THYSTAME] = 0.05f
};

//region Resource utilities
extern void compute_resource_quantities(map_t *map);
//endregion

#endif /* !ZAPPY_SERVER_RESOURCE_H_ */
