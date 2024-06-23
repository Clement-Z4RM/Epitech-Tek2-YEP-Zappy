/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** incantation.h
*/

#ifndef ZAPPY_SERVER_INCANTATION_H_
    #define ZAPPY_SERVER_INCANTATION_H_

    #include <sys/types.h>
    #include <sys/queue.h>
    #include "requests_manager/requests_manager.h"

/**
 * @brief Incantation's players list entry
 */
typedef struct incantation_player_s {
    /** @brief The player */
    ai_client_node_t *player;
    /** @brief The next player */
    SLIST_ENTRY(incantation_player_s) next;
} incantation_player_t;

/**
 * @brief Incantation's players list
 */
SLIST_HEAD(incantation_players_s, incantation_player_s);
typedef struct incantation_players_s incantation_players_t;

// TODO: doc

typedef struct incantation_s {
    u_int8_t level;
    incantation_players_t players;
    u_int64_t x;
    u_int64_t y;
    struct {
        command_updater_t *command_updater;
        command_updaters_t *command_updaters;
    } updater;
    void (*destroy)(struct incantation_s *incantation);
    SLIST_ENTRY(incantation_s) next;
} incantation_t;

SLIST_HEAD(incantations_s, incantation_s);
typedef struct incantations_s incantations_t;

typedef struct incantation_requirements_s {
    u_int8_t players;
    u_int8_t resources[RESOURCES_COUNT];
} incantation_requirements_t;

static const incantation_requirements_t INCANTATIONS_REQUIREMENTS[] = {
    [1] = {
        1,
        {
            [RN_FOOD] = 0,
            [RN_LINEMATE] = 1,
            [RN_DERAUMERE] = 0,
            [RN_SIBUR] = 0,
            [RN_MENDIANE] = 0,
            [RN_PHIRAS] = 0,
            [RN_THYSTAME] = 0
        }
    },
    [2] = {
        2,
        {
            [RN_FOOD] = 0,
            [RN_LINEMATE] = 1,
            [RN_DERAUMERE] = 1,
            [RN_SIBUR] = 1,
            [RN_MENDIANE] = 0,
            [RN_PHIRAS] = 0,
            [RN_THYSTAME] = 0
        }
    },
    [3] = {
        2,
        {
            [RN_FOOD] = 0,
            [RN_LINEMATE] = 2,
            [RN_DERAUMERE] = 0,
            [RN_SIBUR] = 1,
            [RN_MENDIANE] = 0,
            [RN_PHIRAS] = 2,
            [RN_THYSTAME] = 0
        }
    },
    [4] = {
        4,
        {
            [RN_FOOD] = 0,
            [RN_LINEMATE] = 1,
            [RN_DERAUMERE] = 1,
            [RN_SIBUR] = 2,
            [RN_MENDIANE] = 0,
            [RN_PHIRAS] = 1,
            [RN_THYSTAME] = 0
        }
    },
    [5] = {
        4,
        {
            [RN_FOOD] = 0,
            [RN_LINEMATE] = 1,
            [RN_DERAUMERE] = 2,
            [RN_SIBUR] = 1,
            [RN_MENDIANE] = 3,
            [RN_PHIRAS] = 0,
            [RN_THYSTAME] = 0
        }
    },
    [6] = {
        6,
        {
            [RN_FOOD] = 0,
            [RN_LINEMATE] = 1,
            [RN_DERAUMERE] = 2,
            [RN_SIBUR] = 3,
            [RN_MENDIANE] = 0,
            [RN_PHIRAS] = 1,
            [RN_THYSTAME] = 0
        }
    },
    [7] = {
        6,
        {
            [RN_FOOD] = 0,
            [RN_LINEMATE] = 2,
            [RN_DERAUMERE] = 2,
            [RN_SIBUR] = 2,
            [RN_MENDIANE] = 2,
            [RN_PHIRAS] = 2,
            [RN_THYSTAME] = 1
        }
    }
};

extern bool add_players_to_incantation(
    incantation_t *incantation,
    ai_client_node_t *client,
    team_list_t *teams,
    u_int8_t *players
);

extern incantation_t *initiate_incantation(ai_handler_data_t *data);

#endif /* !ZAPPY_SERVER_INCANTATION_H_ */
