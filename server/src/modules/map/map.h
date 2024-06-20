/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** map.h
*/

#ifndef ZAPPY_SERVER_MAP_H_
    #define ZAPPY_SERVER_MAP_H_

    #include <sys/types.h>
    #include <stdbool.h>
    #include "egg/egg.h"
    #include "clients_manager/clients_manager.h"
    #include "resource/resource.h"

/**
 * @brief map_t definition for circular dependency with map_resources_t
 */
typedef struct map_s map_t;

/**
 * @brief Cell structure. It contains the cell's neighbors, its position,
 * and the elements (players, eggs and resources) on it.
 */
typedef struct cell_s {
    /** @brief The cell's up neighbor */
    struct cell_s *up;
    /** @brief The cell's left neighbor */
    struct cell_s *left;

    /** @brief The eggs on the cell */
    eggs_t eggs;
    /** @brief The players on the cell */
    ai_clients_list_t players;
    /** @brief The resources (foods and stones) on the cell */
    u_int64_t resources[RESOURCES_COUNT];

    /** @brief The cell's right neighbor */
    struct cell_s *right;
    /** @brief The cell's down neighbor */
    struct cell_s *down;
} cell_t;

typedef struct map_resources_s {
    /** @brief The quantity of each resource on the map,
     * depending on the width and height of it and the resource density.
     * The last element is the total quantity of resources on the map
     * (all added together) */
    size_t quantities[RESOURCES_COUNT + 1];

    /**
     * @brief Generate resources on the map.
     *
     * @param map The map where the resources are generated.
     */
    void (*generate)(map_t *map);
} map_resources_t;

/**
 * @brief Map structure. It contains the map width and height, and its cells.
 */
typedef struct map_s {
    /** @brief The next egg id */
    u_int64_t egg_id;

    /** @brief The map cells */
    cell_t **cells;
    /** @brief The map width */
    union {
        size_t width;
        size_t x;
    };
    /** @brief The map height */
    union {
        size_t height;
        size_t y;
    };

    /** @brief Helper structure to manage resources
     * (quantities and generation function) on the map */
    map_resources_t resources;

    /** @brief Structure destructor */
    void (*destroy)(struct map_s *map);
} map_t;

extern map_t *create_map(size_t width, size_t height);

//region Helpers
extern void initialize_resources(map_t *map);
//endregion

#endif /* !ZAPPY_SERVER_MAP_H_ */
