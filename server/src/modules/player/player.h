/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** player.h
*/

#ifndef ZAPPY_SERVER_PLAYER_H_
    #define ZAPPY_SERVER_PLAYER_H_

    #include <sys/types.h>
    #include <sys/queue.h>

/**
 * @brief The direction where the player is looking at
 */
typedef enum player_direction_e {
    PD_UP,
    PD_DOWN,
    PD_LEFT,
    PD_RIGHT
} player_direction_t;

/**
 * @brief Player structure.
 * A player (also called a client ; or a Trantorian, an inhabitant of Trantor,
 * the planet where the game takes place) is an entity on the map,
 * which can perform actions like moving, taking objects....
 */
typedef struct player_s {
    /** @brief The amount of time (in time units)
     * the player can still stay alive. If it reaches 0, the player dies */
    u_int64_t life_span;
    /** @brief The direction where the player is looking at */
    player_direction_t direction;
    /** @brief The next player in the list */
    SLIST_ENTRY(player_s) next;
} player_t;

/**
 * @brief Players list
 */
SLIST_HEAD(players_s, player_s);
typedef struct players_s players_t;

#endif /* !ZAPPY_SERVER_PLAYER_H_ */
