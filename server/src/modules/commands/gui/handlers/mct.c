/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** mct command
*/

#include "commands/gui/gui_commands.h"
#include "stdlib.h"
#include "utilities.h"
#include "requests_manager/requests_manager.h"

static void free_mct(char **args, char *x_str, char *y_str)
{
    free(x_str);
    free(y_str);
    free(args);
}

void mct(gui_handler_data_t *data)
{
    map_t *map = data->updater->map;
    char *x_str = (char *)malloc(21);
    char *y_str = (char *)malloc(21);

    data->args = malloc(sizeof(char *) * 4);
    if (!data->args || !x_str || !y_str) {
        free_mct(data->args, x_str, y_str);
        return;
    }
    data->args[1] = x_str;
    data->args[2] = y_str;
    for (size_t y = 0; y < map->height; y++) {
        for (size_t x = 0; x < map->width; x++) {
            snprintf(x_str, 21, "%zu", x);
            snprintf(y_str, 21, "%zu", y);
            bct(data);
        }
    }
    free_mct(data->args, x_str, y_str);
}
