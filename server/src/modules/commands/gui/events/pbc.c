/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** pbc (broadcast) command
*/

#include <string.h>
#include "../gui_commands.h"

void pbc(uint64_t id, char *msg, const clients_manager_t *clients_manager)
{
    char response[MAX_RESPONSE_SIZE];
    gui_client_node_t *node = NULL;

    snprintf(response, MAX_RESPONSE_SIZE, "pbc %lu %s\n", id, msg);
    SLIST_FOREACH(node, &clients_manager->gui_clients_list, next)
        client_add_request(node->client, strdup(response), TO_SEND);
    log_success_broadcast(id, msg);
}
