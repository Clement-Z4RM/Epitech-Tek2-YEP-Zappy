/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** look_directions.c
*/

#include "look.h"
#include <string.h>

static void pass_trough_cells_north(cell_t *cell, int i, int *x_forward, char
    **buffer)
{
    char cell_info[256];

    for (int j = 0; j != i * 2 + 1; j++) {
        if (cell) {
            cell_info[0] = '\0';
            fill_cell_info(cell, cell_info);
            strncat(*buffer, cell_info, 4096 - strlen(*buffer) - 1);
            if (i != 0)
                cell = cell->right;
            (*x_forward)++;
        }
        if (j != i * 2 + 1)
            strncat(*buffer, ",", 4096 - strlen(*buffer) - 1);
    }
}

char *look_north(map_t *map, player_t *player)
{
    cell_t *player_cell = &map->cells[player->y][player->x];
    cell_t *cell = player_cell;
    int x_forward = 0;
    char *buffer = malloc(4096);

    if (!buffer) {
        fprintf(stderr, "look_north: error malloc\n");
        return NULL;
    }
    snprintf(buffer, 2, "[");
    for (int i = 0; i < player->level + 1; i++) {
        if (i != 0)
            back_to_x_left(cell, i, x_forward);
        x_forward = 0;
        if (cell && cell->up && i != 0)
            cell = cell->up;
        pass_trough_cells_north(cell, i, &x_forward, &buffer);
    }
    snprintf(buffer + strlen(buffer) - 1, 2, "]");
    return buffer;
}

static void pass_trough_cells_south(cell_t *cell, int i, int *x_forward, char
    **buffer)
{
    char cell_info[256];

    for (int j = 0; j != i * 2 + 1; j++) {
        if (cell) {
            cell_info[0] = '\0';
            fill_cell_info(cell, cell_info);
            strncat(*buffer, cell_info, 4096 - strlen(*buffer) - 1);
            if (i != 0)
                cell = cell->left;
            (*x_forward)++;
        }
        if (j != i * 2 + 1)
            strncat(*buffer, ",", 4096 - strlen(*buffer) - 1);
    }
}

char *look_south(map_t *map, player_t *player)
{
    cell_t *player_cell = &map->cells[player->y][player->x];
    cell_t *cell = player_cell;
    int x_forward = 0;
    char *buffer = malloc(4096);

    if (!buffer) {
        fprintf(stderr, "look_north: error malloc\n");
        return NULL;
    }
    snprintf(buffer, 2, "[");
    for (int i = 0; i < player->level + 1; i++) {
        if (i != 0)
            back_to_x_right(cell, i, x_forward);
        x_forward = 0;
        if (cell && cell->down && i != 0)
            cell = cell->down;
        pass_trough_cells_south(cell, i, &x_forward, &buffer);
    }
    snprintf(buffer + strlen(buffer) - 1, 2, "]");
    return buffer;
}

static void pass_trough_cells_west(cell_t *cell, int i, int *y_forward, char
    **buffer)
{
    char cell_info[256];

    for (int j = 0; j != i * 2 + 1; j++) {
        if (cell) {
            cell_info[0] = '\0';
            fill_cell_info(cell, cell_info);
            strncat(*buffer, cell_info, 4096 - strlen(*buffer) - 1);
            if (i != 0)
                cell = cell->up;
            (*y_forward)++;
        }
        if (j != i * 2 + 1)
            strncat(*buffer, ",", 4096 - strlen(*buffer) - 1);
    }
}

char *look_west(map_t *map, player_t *player)
{
    cell_t *player_cell = &map->cells[player->y][player->x];
    cell_t *cell = player_cell;
    int y_forward = 0;
    char *buffer = malloc(4096);

    if (!buffer) {
        fprintf(stderr, "look_north: error malloc\n");
        return NULL;
    }
    snprintf(buffer, 2, "[");
    for (int i = 0; i < player->level + 1; i++) {
        if (i != 0)
            back_to_y_down(cell, i, y_forward);
        y_forward = 0;
        if (cell && cell->right && i != 0)
            cell = cell->right;
        pass_trough_cells_west(cell, i, &y_forward, &buffer);
    }
    snprintf(buffer + strlen(buffer) - 1, 2, "]");
    return buffer;
}

static void pass_trough_cells_east(cell_t *cell, int i, int *y_forward, char
    **buffer)
{
    char cell_info[256];

    for (int j = 0; j != i * 2 + 1; j++) {
        if (cell) {
            cell_info[0] = '\0';
            fill_cell_info(cell, cell_info);
            strncat(*buffer, cell_info, 4096 - strlen(*buffer) - 1);
            if (i != 0)
                cell = cell->down;
            (*y_forward)++;
        }
        if (j != i * 2 + 1)
            strncat(*buffer, ",", 4096 - strlen(*buffer) - 1);
    }
}

char *look_east(map_t *map, player_t *player)
{
    cell_t *player_cell = &map->cells[player->y][player->x];
    cell_t *cell = player_cell;
    int y_forward = 0;
    char *buffer = malloc(4096);

    if (!buffer) {
        fprintf(stderr, "look_north: error malloc\n");
        return NULL;
    }
    snprintf(buffer, 2, "[");
    for (int i = 0; i < player->level + 1; i++) {
        if (i != 0)
            back_to_y_up(cell, i, y_forward);
        if (cell && cell->left && i != 0)
            cell = cell->left;
        y_forward = 0;
        pass_trough_cells_east(cell, i, &y_forward, &buffer);
    }
    snprintf(buffer + strlen(buffer) - 1, 2, "]");
    return buffer;
}
