/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** seg command
*/

#include <string.h>
#include "../gui_commands.h"

void seg(char *team_name, clients_manager_t *clients_manager)
{
    char *response = malloc(MAX_RESPONSE_SIZE);
    gui_client_node_t *node = NULL;

    if (response)
        snprintf(response, MAX_RESPONSE_SIZE, "seg %s\n", team_name);
    SLIST_FOREACH(node, &clients_manager->gui_clients_list, next) {
        if (response)
            client_add_request(node->client, response, TO_SEND);
        else
            client_add_request(node->client, strdup("ok\n"), TO_SEND);
    }
}
