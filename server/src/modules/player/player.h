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
    #include "resource/resource.h"

/**
 * @brief The direction where the player is looking at
 */
typedef enum player_direction_e {
    PD_UP = 1, /* NORTH */
    PD_RIGHT,  /* EAST */
    PD_DOWN,   /* SOUTH */
    PD_LEFT    /* WEST */
} player_direction_t;

typedef enum player_rotation_e {
    PR_LEFT = -1,
    PR_RIGHT = 1
} player_rotation_t;

/**
 * @brief Player structure.
 * A player (also called a client ; or a Trantorian, an inhabitant of Trantor,
 * the planet where the game takes place) is an entity on the map,
 * which can perform actions like moving, taking objects....
 */
typedef struct player_s {
    /** @brief The amount of time (in time units)
     * the player can still stay alive. If it reaches 0, the player dies */
    double life_span; // TODO: init to 1260

    /** @brief The player's x position on the map */
    u_int64_t x;
    /** @brief The player's y position on the map */
    u_int64_t y;

    /** @brief The direction where the player is looking at */
    player_direction_t direction;

    /** @brief The resources (foods and stones) in the player's inventory */
    u_int64_t resources[RESOURCES_COUNT];
} player_t;

#endif /* !ZAPPY_SERVER_PLAYER_H_ */
