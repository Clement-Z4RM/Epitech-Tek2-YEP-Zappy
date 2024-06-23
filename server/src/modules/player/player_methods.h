/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** player_utilities.h
*/

#ifndef ZAPPY_SERVER_PLAYER_UTILITIES_H_
    #define ZAPPY_SERVER_PLAYER_UTILITIES_H_

    #include "map/map.h"

extern bool initialize_player(
    ai_client_node_t *client,
    map_t *map,
    team_node_t *team,
    u_int64_t id
);

//region Player actions
extern void player_go_forward(ai_client_node_t *client, map_t *map);

extern void player_turn(ai_client_node_t *client, player_rotation_t rotation);

extern bool player_take_resource(
    ai_client_node_t *client,
    map_t *map,
    resource_name_t resource
);

extern bool player_drop_resource(
    ai_client_node_t *client,
    map_t *map,
    resource_name_t resource
);
//endregion

#endif /* !ZAPPY_SERVER_PLAYER_UTILITIES_H_ */
