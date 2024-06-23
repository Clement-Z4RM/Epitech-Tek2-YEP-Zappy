/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** look_around_fill_buffer.c
*/

#include "requests_manager/requests_manager.h"
#include <string.h>

static void fill_resource_buffer(char **current_cell, char *tmp_buffer)
{
    char *tmp = NULL;

    tmp = *current_cell;
    *current_cell = malloc(strlen(*current_cell) + strlen(tmp_buffer) + 1);
    if (!*current_cell) {
        free(tmp);
        return;
    }
    strcpy(*current_cell, tmp);
    strcat(*current_cell, tmp_buffer);
    free(tmp);
}

void fill_resource(char **current_cell, int i)
{
    char tmp_buffer[256];

    if (i == RN_FOOD)
        snprintf(tmp_buffer, sizeof(tmp_buffer), "food");
    else
        snprintf(tmp_buffer, sizeof(tmp_buffer), "%s", RESOURCE_NAMES[i]);
    if (*current_cell) {
        fill_resource_buffer(current_cell, tmp_buffer);
    } else {
        *current_cell = strdup(tmp_buffer);
        if (!*current_cell) {
            return;
        }
    }
}

void fill_current_cell_resource(cell_t *cell, char **current_cell)
{
    if ((*current_cell) && (*current_cell)[strlen(*current_cell) - 1] != '\0')
        snprintf(*current_cell + strlen(*current_cell), 254, " ");
    for (int i = 0; i < RESOURCES_COUNT; i++) {
        if (cell->resources[i] > 0) {
            fill_resource(current_cell, i);
        }
        if (*current_cell && i + 1 < RESOURCES_COUNT &&
            cell->resources[i + 1] > 0) {
            snprintf(*current_cell + strlen(*current_cell), 254, " ");
        }
    }
}

void fill_player(char **current_cell)
{
    char tmp_buffer[256];
    char *tmp = NULL;

    snprintf(tmp_buffer, sizeof(tmp_buffer), "player");
    if (*current_cell) {
        tmp = *current_cell;
        *current_cell = malloc(strlen(*current_cell) + strlen(tmp_buffer) + 1);
        if (!*current_cell) {
            free(tmp);
            return;
        }
        strcpy(*current_cell, tmp);
        strcat(*current_cell, tmp_buffer);
        free(tmp);
    } else {
        *current_cell = strdup(tmp_buffer);
        if (!*current_cell) {
            return;
        }
    }
}

void fill_cell_info(cell_t *cell, char *buffer)
{
    char *current_cell = malloc(sizeof(char) * 256);
    ai_client_node_t *player;

    SLIST_FOREACH(player, &cell->players, next) {
        if (current_cell && current_cell[strlen(current_cell) - 1] != '\0')
            snprintf(current_cell + strlen(current_cell), 254, " ");
        fill_player(&current_cell);
    }
    fill_current_cell_resource(cell, &current_cell);
    if (current_cell && current_cell[0] != '\0') {
        strncpy(buffer, current_cell, 254);
        buffer[255] = '\0';
        free(current_cell);
    } else {
        buffer[0] = '\0';
    }
}
