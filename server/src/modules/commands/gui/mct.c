/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** mct command
*/

#include "gui_commands.h"
#include "stdlib.h"

void mct(gui_handler_data_t *data)
{
    map_t *map = data->map;
    static const uint8_t MAX_DIGITS = 21;
    char *x_str = (char *)malloc(MAX_DIGITS * sizeof(char));
    char *y_str = (char *)malloc(MAX_DIGITS * sizeof(char));

    for (size_t y = 0; y < map->height; y++) {
        for (size_t x = 0; x < map->width; x++) {
            snprintf(x_str, MAX_DIGITS, "%zu", x);
            snprintf(y_str, MAX_DIGITS, "%zu", y);
            data->args[1] = x_str;
            data->args[2] = y_str;
            bct(data);
        }
    }
    free(x_str);
    free(y_str);
}
