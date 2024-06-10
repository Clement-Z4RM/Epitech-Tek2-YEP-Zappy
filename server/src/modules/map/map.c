/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** map.c
*/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "map.h"

static void destroy_cell_elements(cell_t *cell)
{
    void *tmp;

    while (!SLIST_EMPTY(&cell->players)) {
        tmp = SLIST_FIRST(&cell->players);
        SLIST_REMOVE_HEAD(&cell->players, next);
        free(tmp);
    }
    while (!SLIST_EMPTY(&cell->eggs)) {
        tmp = SLIST_FIRST(&cell->eggs);
        SLIST_REMOVE_HEAD(&cell->eggs, next);
        free(tmp);
    }
    while (!SLIST_EMPTY(&cell->resources)) {
        tmp = SLIST_FIRST(&cell->resources);
        SLIST_REMOVE_HEAD(&cell->resources, next);
        free(tmp);
    }
}

/**
 * @brief Map structure destructor
 *
 * @param map The map to destroy
 */
static void map_destructor(map_t *map)
{
    if (!map)
        return;
    for (size_t y = 0; map->cells[y]; ++y) {
        for (size_t x = 0; x < map->width; ++x)
            destroy_cell_elements(&map->cells[y][x]);
        free(map->cells[y]);
    }
    free(map->cells);
    free(map);
}

/**
 * @brief Link a cell of the map with its neighbors
 *
 * @param map The map containing the cells
 * @param y The cell's y position
 * @param x The cell's x position
 */
static void link_cell(map_t *map, size_t y, size_t x)
{
    size_t cells[4][2] = {{x, y - 1}, {x - 1, y}, {x + 1, y}, {x, y + 1}};

    for (u_int8_t i = 0; i < 4; ++i) {
        if ((int)cells[i][0] < 0)
            cells[i][0] = map->width - 1;
        if (cells[i][0] >= map->width)
            cells[i][0] = 0;
        if ((int)cells[i][1] < 0)
            cells[i][1] = map->height - 1;
        if (cells[i][1] >= map->height)
            cells[i][1] = 0;
    }
    map->cells[y][x].up = &map->cells[cells[0][1]][cells[0][0]];
    map->cells[y][x].left = &map->cells[cells[1][1]][cells[1][0]];
    map->cells[y][x].right = &map->cells[cells[2][1]][cells[2][0]];
    map->cells[y][x].down = &map->cells[cells[3][1]][cells[3][0]];
}

/**
 * @brief Link the cells of the map with each other
 *
 * @param map The map containing the cells to link
 */
static void link_cells(map_t *map)
{
    for (size_t y = 0; y < map->y; ++y)
        for (size_t x = 0; x < map->x; ++x) {
            map->cells[y][x].x = x;
            map->cells[y][x].y = y;
            SLIST_INIT(&map->cells[y][x].players);
            SLIST_INIT(&map->cells[y][x].eggs);
            SLIST_INIT(&map->cells[y][x].resources);
            link_cell(map, y, x);
        }
}

/**
 * @brief Initialize the map cells
 *
 * @param map The map containing the cells to initialize
 *
 * @return true if the cells were successfully initialized,
 * false otherwise (allocation error)
 */
static bool initialize_map_cells(map_t *map)
{
    map->cells = malloc(sizeof(cell_t *) * (map->height + 1));
    if (!map->cells) {
        perror("malloc");
        free(map);
        return false;
    }
    map->cells[map->height] = NULL;
    map->destroy = map_destructor;
    for (size_t i = 0; i < map->height; ++i) {
        map->cells[i] = malloc(sizeof(cell_t) * map->width);
        if (!map->cells[i]) {
            perror("malloc");
            map_destructor(map);
            return false;
        }
    }
    link_cells(map);
    return true;
}

/**
 * @brief Initialize the map depending on the width and height
 *
 * @param width Map width
 * @param height Map height
 *
 * @return The created map, or NULL if an allocation error occurred
 */
map_t *create_map(size_t width, size_t height)
{
    map_t *map;

    if ((int)width <= 0 || (int)height <= 0) {
        fprintf(stderr, "Invalid map size: (%ld)x(%ld)\n", width, height);
        return NULL;
    }
    map = malloc(sizeof(map_t));
    if (!map) {
        perror("malloc");
        return NULL;
    }
    map->width = width;
    map->height = height;
    if (!initialize_map_cells(map))
        return NULL;
    compute_resource_quantities(map);
    return map;
}
