/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** look around command
*/

#include "look.h"
#include <string.h>

void back_to_x_left(cell_t *cell, int stage, int x_forward)
{
    for (int i = 0; i < stage + x_forward; i++) {
        cell = cell->left;
    }
}

void back_to_x_right(cell_t *cell, int stage, int x_forward)
{
    for (int i = 0; i < stage + x_forward; i++) {
        cell = cell->right;
    }
}

void back_to_y_up(cell_t *cell, int stage, int y_forward)
{
    for (int i = 0; i < stage + y_forward; i++) {
        cell = cell->up;
    }
}

void back_to_y_down(cell_t *cell, int stage, int y_forward)
{
    for (int i = 0; i < stage + y_forward; i++) {
        cell = cell->down;
    }
}

static char *player_look_updater(map_t *map, player_t *player)
{
    char *buffer = NULL;

    switch (player->direction) {
        case PD_UP:
            buffer = look_north(map, player);
            break;
        case PD_DOWN:
            buffer = look_south(map, player);
            break;
        case PD_RIGHT:
            buffer = look_east(map, player);
            break;
        case PD_LEFT:
            buffer = look_west(map, player);
            break;
    }
    return buffer;
}

static void look_updater(
    ai_client_node_t *client,
    UNUSED updater_t *updater,
    UNUSED char *arg
)
{
    char *buffer = player_look_updater(updater->map, &client->player);

    if (!buffer) {
        client_add_request(client->client, strdup("ko\n"), TO_SEND);
        return;
    }
    client_add_request(client->client, buffer, TO_SEND);
}

void look(ai_handler_data_t *data)
{
    command_updater_data_t updater_data = {
        data->updater->elapsed,
        7,
        data->client,
        NULL
    };

    updater_add_command(data->updater, &updater_data, look_updater);
}
