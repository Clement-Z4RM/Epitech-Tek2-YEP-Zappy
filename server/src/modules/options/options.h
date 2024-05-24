/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** options.h
*/

#ifndef ZAPPY_SERVER_OPTIONS_H_
    #define ZAPPY_SERVER_OPTIONS_H_

#include <sys/types.h>
#include <sys/queue.h>

/**
 * @brief Frequency type (simply an unsigned long)
 */
typedef ulong freq_t;

/**
 * @brief Team name entry
 */
typedef struct team_name_s {
    const char *name;
    SLIST_ENTRY(team_name_s) next;
} team_name_t;

/**
 * @brief Team names list
 */
typedef SLIST_HEAD(team_names_s, team_name_s) team_names_t;

/**
 * @brief Program options structure
 */
typedef struct options_s {
    /** @brief The port number of the server */
    ushort port;
    /** @brief The world size */
    struct {
        /** @brief The width of the world */
        size_t x;
        /** @brief The height of the world */
        size_t y;
    } world;
    /** @brief  The team names. It's a linked list because we don't know
     * the number of teams when options are parsed */
    team_names_t teams;
    /** @brief The number of authorized clients per team */
    ulong clients;
    /** @brief The frequency,
     * the reciprocal of time unit for execution of actions */
    freq_t freq;
} options_t;

#endif /* !ZAPPY_SERVER_OPTIONS_H_ */
