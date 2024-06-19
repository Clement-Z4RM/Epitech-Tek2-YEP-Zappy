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
    client_t *client = data->client->client;
    map_t *map = data->map;
    char width[32];
    char height[32];
    char response[1024];

    snprintf(width, sizeof(width), "%zu", map->width);
    snprintf(height, sizeof(height), "%zu", map->height);
    if (strlen(width) < MAX_RESPONSE_SIZE &&
        strlen(height) < MAX_RESPONSE_SIZE
    ) {
        snprintf(response, MAX_RESPONSE_SIZE, "msz %s %s\n", width, height);
    } else {
        return;
    }
    client_add_request(client, response, TO_SEND);
}
