/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** command msz
*/

#include "gui_commands.h"

void msz(client_t *client, UNUSED client_manager_t *client_manager, map_t *map)
{
    char width[32];
    char height[32];
    char *response = NULL;

    snprintf(width, sizeof(width), "%zu", map->width);
    snprintf(height, sizeof(height), "%zu", map->height);
    asprintf(&response, "msz %s %s\n", width, height);
    client_add_request(client, response, TO_SEND);
}
