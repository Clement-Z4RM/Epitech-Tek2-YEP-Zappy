/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** pex command (expulsion)
*/

#include <string.h>
#include "../gui_commands.h"

void pex(uint64_t id, const clients_manager_t *clients_manager)
{
    char *response = malloc(MAX_RESPONSE_SIZE);
    const gui_client_node_t *node = NULL;

    if (response)
        snprintf(response, MAX_RESPONSE_SIZE, "pex %lu\n", id);
    SLIST_FOREACH(node, &clients_manager->gui_clients_list, next) {
        if (response)
            client_add_request(node->client, response, TO_SEND);
        else
            client_add_request(node->client, strdup("ko\n"), TO_SEND);
    }
}
