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
    char *response = malloc(MAX_RESPONSE_SIZE);
    gui_client_node_t *node = NULL;

    if (response)
        snprintf(response, MAX_RESPONSE_SIZE, "pbc %lu %s\n", id, msg);
    SLIST_FOREACH(node, &clients_manager->gui_clients_list, next) {
        if (response)
            client_add_request(node->client, response, TO_SEND);
        else
            client_add_request(node->client, strdup("ko\n"), TO_SEND);
    }
    log_success_broadcast(id, msg);
}
