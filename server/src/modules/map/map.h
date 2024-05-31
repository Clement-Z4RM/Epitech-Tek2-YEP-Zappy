/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** map.h
*/

#ifndef ZAPPY_SERVER_MAP_H_
    #define ZAPPY_SERVER_MAP_H_

    #include <sys/types.h>

typedef struct cell_s {
    /** @brief The cell's up neighbor */
    struct cell_s *up;
    /** @brief The cell's left neighbor */
    struct cell_s *left;

    // TODO: are x & y useful?

    /** @brief The cell's x position */
    uint x;
    /** @brief The cell's y position */
    uint y;

    // TODO: Add elements on cell (players and resources)

    /** @brief The cell's right neighbor */
    struct cell_s *right;
    /** @brief The cell's down neighbor */
    struct cell_s *down;
} cell_t;

typedef struct map_s {
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

    /** @brief Structure destructor */
    void (*destroy)(struct map_s *map);
} map_t;

extern map_t *create_map(size_t width, size_t height);

#endif /* !ZAPPY_SERVER_MAP_H_ */
