/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** command bct
*/

#include "gui_commands.h"
#include "requests_manager/requests_manager.h"
#include "stdlib.h"

void bct(gui_handler_data_t *data)
{
    char *end_ptr = NULL;
    int64_t x = strtol(data->args[1], &end_ptr, 10);
    int64_t y = strtol(data->args[2], &end_ptr, 10);
    cell_t *cell = NULL;
    char response[1024];

    if (x < 0 || x >= (int64_t)data->map->width
        || y < 0 || y >= (int64_t)data->map->height)
        return;
    cell = &data->map->cells[y][x];
    snprintf(response, sizeof(response),
        "bct %ld %ld %ld %ld %ld %ld %ld %ld %ld\n",
        x, y,
        cell->resources[RN_FOOD], cell->resources[RN_LINEMATE],
        cell->resources[RN_DERAUMERE], cell->resources[RN_SIBUR],
        cell->resources[RN_MENDIANE], cell->resources[RN_PHIRAS],
        cell->resources[RN_THYSTAME]
    );
    client_add_request(data->client->client, response, TO_SEND);
}
