/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** command msz
*/

#include "commands/gui/gui_commands.h"
#include "requests_manager/requests_manager.h"
#include "string.h"

void msz(gui_handler_data_t *data)
{
    client_t *client = data->gui_client->client;
    map_t *map = data->updater->map;
    char *response = malloc(1024);

    if (!response) {
        client_add_request(data->gui_client->client, strdup("ok\n"), TO_SEND);
        return;
    }
    snprintf(response, MAX_RESPONSE_SIZE, "msz %zu %zu\n",
        map->width, map->height);
    client_add_request(client, response, TO_SEND);
}
