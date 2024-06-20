/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** egg.h
*/

#ifndef ZAPPY_SERVER_EGG_H_
    #define ZAPPY_SERVER_EGG_H_

    #include <sys/types.h>
    #include <sys/queue.h>

/**
 * @brief Egg structure
 */
typedef struct egg_s {
    /** @brief The egg id */
    u_int64_t id;

    /** @brief The egg's x position on the map */
    u_int64_t x;
    /** @brief The egg's y position on the map */
    u_int64_t y;

    /** @brief The next egg in the list */
    SLIST_ENTRY(egg_s) next;
} egg_t;

/**
 * @brief Eggs list
 */
SLIST_HEAD(eggs_s, egg_s);
typedef struct eggs_s eggs_t;

/**
 * @brief Team's eggs list entry
 */
typedef struct team_egg_s {
    egg_t *egg;
    SLIST_ENTRY(team_egg_s) next;
} team_egg_t;

/**
 * @brief Team's eggs list
 */
SLIST_HEAD(team_eggs_s, team_egg_s);
typedef struct team_eggs_s team_eggs_t;

#endif /* !ZAPPY_SERVER_EGG_H_ */
