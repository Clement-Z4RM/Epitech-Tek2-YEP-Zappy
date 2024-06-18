/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** player_utilities.h
*/

#ifndef ZAPPY_SERVER_PLAYER_UTILITIES_H_
    #define ZAPPY_SERVER_PLAYER_UTILITIES_H_

    #include "map/map.h"

extern void player_go_forward(ai_client_node_t *client, map_t *map);
extern void player_turn(ai_client_node_t *client, player_rotation_t rotation);

#endif /* !ZAPPY_SERVER_PLAYER_UTILITIES_H_ */
