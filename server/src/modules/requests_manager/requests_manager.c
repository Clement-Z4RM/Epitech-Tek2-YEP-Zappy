/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** Requests_manager module
*/

#include "requests_manager.h"
#include "stdlib.h"
#include <string.h>
#include "utilities.h"
#include "logs/failures/logs_failures.h"

/**
* @brief check if the client has a team name
* @param client the client to check
* @param clients_manager the clients manager
* @return bool true if the client has a team name, false otherwise
**/
static bool requests_manager_have_team_name(
    client_t *client,
    client_manager_t *clients_manager
)
{
    if (client->team_name == NULL) {
        client->team_name = client->current_request_to_handle;
        client->current_request_to_handle = NULL;
        if (strcmp(client->team_name, "GRAPHIC") == 0)
            clients_manager_add(clients_manager, client, GUI);
        else
            clients_manager_add(clients_manager, client, AI);
        return false;
    }
    return true;
}

/**
* @brief freeing memory of the currently handled request
* @param args parsed args of the request
* @param client the client that sent the request
**/
static void requests_manager_free_request_memory(char **args, client_t *client)
{
    if (client->current_request_to_handle)
        free(client->current_request_to_handle);
    client->current_request_to_handle = NULL;
    free_double_tab(args);
}

static bool requests_manager_handle_gui_request(
    char **args,
    client_t *client,
    client_manager_t *clients_manager
)
{
    gui_handler_data_t handler_data = {client, args, clients_manager};

    for (int i = 0; i < GUI_HANDLERS_COUNT; i++) {
        if (gui_request_handlers[i].command_name == NULL)
            continue;
        if (strcmp(gui_request_handlers[i].command_name, args[0]) == 0) {
            gui_request_handlers[i].handler(&handler_data);
            return true;
        }
    }
    return false;
}

static bool requests_manager_handle_ai_request(
    char **args,
    client_t *client,
    client_manager_t *clients_manager
)
{
    ai_handler_data_t handler_data = {client, args, clients_manager};

    for (int i = 0; i < AI_HANDLERS_COUNT; i++) {
        if (ai_request_handlers[i].command_name == NULL)
            continue;
        if (strcmp(ai_request_handlers[i].command_name, args[0]) == 0) {
            ai_request_handlers[i].handler(&handler_data);
            return true;
        }
    }
    return false;
}

/**
* @brief handle the request of the client
* @param client the client that sent the request
* @param clients_manager the clients manager
**/
static void requests_manager_handle_request(client_t *client,
    client_manager_t *clients_manager)
{
    char **args = NULL;

    remove_newline(client->current_request_to_handle);
    if (!requests_manager_have_team_name(client, clients_manager))
        return;
    args = str_array_split(client->current_request_to_handle, " ");
    if (args == NULL || args[0] == NULL)
        return;
    if (client->type == AI)
        if (!requests_manager_handle_ai_request(args, client, clients_manager))
            log_request_no_handler(client);
    if (client->type == GUI)
        if (!requests_manager_handle_gui_request(args,
            client, clients_manager))
            log_request_no_handler(client);
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
