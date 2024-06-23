/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** look_around.h
*/

#pragma once

#include "requests_manager/requests_manager.h"

//fill
extern void fill_resource(char **current_cell, int i);

extern void fill_current_cell_resource(cell_t *cell, char **current_cell);

extern void fill_player(char **current_cell);

extern void fill_cell_info(cell_t *cell, char *buffer);

//back_to
extern void back_to_x_left(cell_t *cell, int stage, int x_forward);

extern void back_to_x_right(cell_t *cell, int stage, int x_forward);

extern void back_to_y_up(cell_t *cell, int stage, int y_forward);

extern void back_to_y_down(cell_t *cell, int stage, int y_forward);

//look by directions
extern char *look_east(map_t *map, player_t *player);

extern char *look_west(map_t *map, player_t *player);

extern char *look_north(map_t *map, player_t *player);

extern char *look_south(map_t *map, player_t *player);
