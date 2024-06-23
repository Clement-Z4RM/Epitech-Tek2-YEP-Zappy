/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** command bct
*/

#include <stdlib.h>
#include <string.h>
#include "commands/gui/gui_commands.h"
#include "requests_manager/requests_manager.h"

static void fill_response(char *response, cell_t *cell, int64_t x, int64_t y)
{
    snprintf(response, 1024,
        "bct %ld %ld %ld %ld %ld %ld %ld %ld %ld\n",
        x, y,
        cell->resources[RN_FOOD], cell->resources[RN_LINEMATE],
        cell->resources[RN_DERAUMERE], cell->resources[RN_SIBUR],
        cell->resources[RN_MENDIANE], cell->resources[RN_PHIRAS],
        cell->resources[RN_THYSTAME]
    );
}

void bct(gui_handler_data_t *data)
{
    char *end_ptr = NULL;
    int64_t x = strtol(data->args[1], &end_ptr, 10);
    int64_t y = strtol(data->args[2], &end_ptr, 10);
    cell_t *cell = NULL;
    char *response = malloc(1024);

    if (!response) {
        client_add_request(data->gui_client->client, strdup("ko\n"), TO_SEND);
        return;
    }
    if (x < 0 || x >= (int64_t)data->updater->map->width
        || y < 0 || y >= (int64_t)data->updater->map->height)
        return;
    cell = &data->updater->map->cells[y][x];
    fill_response(response, cell, x, y);
    client_add_request(data->gui_client->client, response, TO_SEND);
}
