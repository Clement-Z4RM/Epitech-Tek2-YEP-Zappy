/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** Requests_manager module
*/

#include "requests_manager.h"
#include "stdlib.h"
#include <string.h>
#include "../../include/utilities.h"

static char **requests_manager_parse_args(char *request)
{
    char **args = str_array_split(request, " ");

    return args;
}

static void requests_manager_handle_request(char *request, client_t *client,
    client_manager_t *clients_manager)
{
    char **args = requests_manager_parse_args(request);
    handler_data_t handler_data = {client, args, clients_manager};

    if (args == NULL || args[0] == NULL)
        return;
    for (int i = 0; i < HANDLERS_COUNT; i++) {
        if (request_handlers[i].command_name == NULL)
            continue;
        if (strcmp(request_handlers[i].command_name, args[0]) == 0) {
            request_handlers[i].handler(&handler_data);
            break;
        }
    }
    free(args);
}

void requests_manager_handle_requests(client_manager_t *clients_manager)
{
    client_node_t *current = NULL;
    client_request_node_t *current_request = NULL;
    client_t *client = NULL;

    while (!SLIST_EMPTY(&clients_manager->clients_list)) {
        current = SLIST_FIRST(&clients_manager->clients_list);
        client = current->client;
        SLIST_REMOVE_HEAD(&clients_manager->clients_list, next);
        if (client->current_request_to_handle == NULL) {
            current_request = CIRCLEQ_LAST(
                &client->requests_queue_to_handle);
            client->current_request_to_handle = current_request->request;
            CIRCLEQ_REMOVE(&current->client->requests_queue_to_handle,
                current_request, next);
            requests_manager_handle_request(
                current->client->current_request_to_handle,
                current->client, clients_manager
            );
        }
    }
}
