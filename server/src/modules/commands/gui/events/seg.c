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
    char response[MAX_RESPONSE_SIZE];
    gui_client_node_t *node = NULL;

    snprintf(response, MAX_RESPONSE_SIZE, "seg %s\n", team_name);
    SLIST_FOREACH(node, &clients_manager->gui_clients_list, next)
        client_add_request(node->client, strdup(response), TO_SEND);
}
