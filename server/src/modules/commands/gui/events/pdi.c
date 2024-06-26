/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** pdi command
*/

#include <string.h>
#include "../gui_commands.h"
//TODO: send log failure if response is NULL
void pdi(const uint64_t id, clients_manager_t *clients_manager)
{
    char response[MAX_RESPONSE_SIZE];
    gui_client_node_t *node = NULL;

    snprintf(response, MAX_RESPONSE_SIZE, "pdi %lu\n", id);
    SLIST_FOREACH(node, &clients_manager->gui_clients_list, next)
        client_add_request(node->client, strdup(response), TO_SEND);
    log_success_pdi(id);
}
