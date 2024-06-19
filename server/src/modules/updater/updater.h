/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** updater.h
*/

#ifndef ZAPPY_SERVER_UPDATER_H_
    #define ZAPPY_SERVER_UPDATER_H_

    #include <time.h>
    #include "network/network.h"
    #include "map/map.h"

/**
 * @brief Updater structure
 */
typedef struct updater_s {
    /** @brief The time (in milliseconds) when the last update happened */
    time_t previous_time;

    /** @brief The time (in milliseconds) between two resource generations */
    time_t generation_interval;
    /** @brief The time (in milliseconds) when the next resource generation
     * will happen */
    time_t next_generation;

    /** @brief A pointer to the network structure */
    network_t *network;
    /** @brief A pointer to the map structure */
    map_t *map;

    /** @brief The update function */
    void (*update)(struct updater_s *updater, time_t elapsed);

    /** @brief Structure destructor */
    void (*destroy)(struct updater_s *updater);
} updater_t;

extern updater_t *create_updater(network_t *network, map_t *map);

#endif /* !ZAPPY_SERVER_UPDATER_H_ */
