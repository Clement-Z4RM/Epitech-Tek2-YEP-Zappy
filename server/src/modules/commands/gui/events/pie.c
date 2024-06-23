/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** pie command
*/

#include "../gui_commands.h"
#include <string.h>

void pie(
    uint64_t x,
    uint64_t y,
    bool result,
    clients_manager_t *clients_manager)
{
    char response[50];
    gui_client_node_t *gui_client = NULL;

    snprintf(response, 50, "pie %lu %lu %d\n", x, y, result);
    SLIST_FOREACH(gui_client, &clients_manager->gui_clients_list, next)
        client_add_request(gui_client->client, strdup(response), TO_SEND);
}
