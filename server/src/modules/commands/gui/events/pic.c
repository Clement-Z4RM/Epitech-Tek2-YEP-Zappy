/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** pic command
*/

#include <stdarg.h>
#include "../gui_commands.h"

static void fill_response_with_ai_ids(char *response, uint64_t *ids, int *len)
{
    uint64_t id = 0;
    int ret = 0;

    for (int i = 0; ids[i] != 0; i++) {
        id = ids[i];
        ret = snprintf(response + *len, MAX_RESPONSE_SIZE - *len, " #%lu", id);
        if (ret < 0 || ret >= MAX_RESPONSE_SIZE - *len)
            return;
        *len += ret;
    }
}

//TODO: error log on len < 0 or len >= MAX_RESPONSE_SIZE
void pic(const uint8_t level, va_list *ap, const clients_manager_t
    *clients_manager)
{
    char response[MAX_RESPONSE_SIZE];
    gui_client_node_t *node = NULL;
    uint64_t *ids = va_arg(*ap, uint64_t *);
    int len = snprintf(response, MAX_RESPONSE_SIZE, "pic %d", level);

    if (len < 0 || len >= MAX_RESPONSE_SIZE)
        return;
    fill_response_with_ai_ids(response, ids, &len);
    if (len < MAX_RESPONSE_SIZE - 1) {
        response[len] = '\n';
        response[len + 1] = '\0';
    } else {
        return;
    }
    SLIST_FOREACH(node, &clients_manager->gui_clients_list, next) {
        client_add_request(node->client, response, TO_SEND);
    }
}
