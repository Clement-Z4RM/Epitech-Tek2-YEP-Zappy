/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** updater.h
*/

#ifndef ZAPPY_SERVER_UPDATER_H_
    #define ZAPPY_SERVER_UPDATER_H_

    #include <sys/queue.h>
    #include <time.h>
    #include "network/network.h"
    #include "map/map.h"

/**
 * @brief updater_t definition for circular dependency with command_updater_t
 */
typedef struct updater_s updater_t;

/**
 * @brief Command updater function type
 *
 * @param client The client that requested the command
 * @param updater The updater structure
 * @param arg The optional argument of the command
 */
typedef void (*command_updater_func_t)(
    ai_client_node_t *client,
    updater_t *updater,
    void *arg
);

/**
 * @brief Command updater data structure
 */
typedef struct command_updater_data_s {
    /** @brief The time (in milliseconds) when the command was executed */
    time_t executed_at;
    /** @brief The time the command takes to execute.
     * For example, a command that takes 7 ticks (7/f)
     * to execute will have a time of 7 */
    time_t time;

    /** @brief The client that requested the command */
    ai_client_node_t *client;
    /** @brief The id of the client.
     * Used to check if client is still connected */
    u_int64_t id;

    /** @brief The optional argument of the command updater function.
     * It should be allocated to avoid memory issues and free if necessary.
     * It will be freed if client is disconnected */
    void *arg;
} command_updater_data_t;

/**
 * @brief Command updater structure
 */
typedef struct command_updater_s {
    /** @brief The data of the command updater */
    command_updater_data_t data;
    /** @brief The command updater function */
    command_updater_func_t updater;
    /** @brief The next command updater in the list */
    CIRCLEQ_ENTRY(command_updater_s) next;
} command_updater_t;

/**
 * @brief Command updaters list
 */
CIRCLEQ_HEAD(command_updaters_s, command_updater_s);
typedef struct command_updaters_s command_updaters_t;

/**
 * @brief Updater structure
 */
typedef struct updater_s {
    /** @brief The time (in milliseconds) when the game started */
    time_t start;

    /** @brief The total time (in milliseconds) elapsed since the game start
     * (updated at each loop iteration) */
    time_t elapsed;

    /** @brief The time (in milliseconds) when the last update happened */
    time_t previous_time;

    /** @brief The time (in milliseconds) between two resource generations */
    time_t generation_interval;
    /** @brief The time (in milliseconds) when the next resource generation
     * will happen */
    time_t next_generation;

    /** @brief The command updaters to call after a certain amount of time */
    command_updaters_t command_updaters;

    /** @brief A pointer to the network structure */
    network_t *network;
    /** @brief A pointer to the map structure */
    map_t *map;

    bool end_of_game;

    /** @brief The update function */
    void (*update)(struct updater_s *updater);

    /** @brief Structure destructor */
    void (*destroy)(struct updater_s *updater);
} updater_t;

extern updater_t *create_updater(network_t *network, map_t *map);

extern command_updater_t *updater_add_command(
    updater_t *updater,
    command_updater_data_t *data,
    command_updater_func_t command_updater_func
);

extern void updater_execute_commands(updater_t *updater);

#endif /* !ZAPPY_SERVER_UPDATER_H_ */
