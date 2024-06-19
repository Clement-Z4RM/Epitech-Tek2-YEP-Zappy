/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** pic command
*/

#include <stdarg.h>
#include "../gui_commands.h"

void pic(const uint8_t level, va_list *ap, const clients_manager_t
    *clients_manager)
{
    char response[MAX_RESPONSE_SIZE];
    gui_client_node_t *node = NULL;
    uint64_t *ids = va_arg(*ap, uint64_t *);
    uint64_t id = 0;

    snprintf(response, MAX_RESPONSE_SIZE, "pic %d", level);
    for (uint8_t i = 0; ids[i] != 0; i++) {
        id = ids[i];
        snprintf(response, MAX_RESPONSE_SIZE, "%s #%lu", response, id);
    }
    snprintf(response, MAX_RESPONSE_SIZE, "%s\n", response);
    SLIST_FOREACH(node, &clients_manager->gui_clients_list, next)
    {
        client_add_request(node->client, response, TO_SEND);
    }
}
