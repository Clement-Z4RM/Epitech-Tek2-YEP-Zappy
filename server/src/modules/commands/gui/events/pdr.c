/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** pdr.c
*/

#include <string.h>
#include "../gui_commands.h"

void pdr(uint64_t id,
    resource_name_t resource,
    clients_manager_t *clients_manager
)
{
    char response[MAX_RESPONSE_SIZE];
    const gui_client_node_t *node = NULL;

    snprintf(response, MAX_RESPONSE_SIZE, "pdr %lu %d\n", id, resource);
    SLIST_FOREACH(node, &clients_manager->gui_clients_list, next)
        client_add_request(node->client, strdup(response), TO_SEND);
    log_success_set(id, resource);
    pin_event(id, clients_manager);
}
