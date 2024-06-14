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

static bool requests_manager_have_team_name(client_t *client)
{
    if (client->team_name == NULL) {
        client->team_name = client->current_request_to_handle;
        client->current_request_to_handle = NULL;
        return false;
    }
    return true;
}

static void requests_manager_free_request_memory(char **args, client_t *client)
{
    if (client->current_request_to_handle)
        free(client->current_request_to_handle);
    client->current_request_to_handle = NULL;
    free_double_tab(args);
}

static void requests_manager_handle_request(client_t *client,
    client_manager_t *clients_manager)
{
    char **args = NULL;
    handler_data_t handler_data = {client, args, clients_manager};

    remove_newline(client->current_request_to_handle);
    if (requests_manager_have_team_name(client))
        return;
    args = str_array_split(client->current_request_to_handle, " ");
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
    requests_manager_free_request_memory(args, client);
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
                current->client, clients_manager
            );
        }
    }
}
