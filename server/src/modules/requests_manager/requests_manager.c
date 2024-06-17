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
#include "logs/successes/logs_successes.h"

/**
* @brief check if the client has a team name
* @param client the client to check
* @param clients_manager the clients manager
* @return bool true if the client has a team name, false otherwise
**/
static bool requests_manager_add_to_team(
    client_t *client,
    client_manager_t *clients_manager
)
{
    client->team_name = client->current_request_to_handle;
    client->current_request_to_handle = NULL;
    if (strcmp(client->team_name, "GRAPHIC") == 0) {
        return clients_manager_add(clients_manager, client, GUI);
    }
    if (clients_manager_add_to_team(
        clients_manager,
        client,
        client->team_name) == false) {
        return false;
    }
    return clients_manager_add(clients_manager, client, AI);
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
    client_manager_t *clients_manager,
    map_t *map
)
{
    gui_handler_data_t handler_data = {client, args, clients_manager, map};

    for (size_t i = 0; i < GUI_HANDLERS_COUNT; i++) {
        if (GUI_HANDLERS[i].command_name == NULL)
            continue;
        if (strcmp(GUI_HANDLERS[i].command_name, args[0]) == 0) {
            GUI_HANDLERS[i].handler(&handler_data);
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

    for (size_t i = 0; i < AI_HANDLERS_COUNT; i++) {
        if (AI_HANDLERS[i].command_name == NULL)
            continue;
        if (strcmp(AI_HANDLERS[i].command_name, args[0]) == 0) {
            AI_HANDLERS[i].handler(&handler_data);
            return true;
        }
    }
    return false;
}

static void requests_manager_handle_request_on_client_type(
    client_t *client,
    char **args,
    client_manager_t *clients_manager,
    map_t *map
)
{
    if (client->type == AI)
        if (!requests_manager_handle_ai_request(args, client, clients_manager))
            log_failure_request_no_handler(client);
    if (client->type == GUI)
        if (!requests_manager_handle_gui_request(args,
            client, clients_manager, map))
            log_failure_request_no_handler(client);
}

static bool requests_manager_client_have_team(
    client_t *client,
    client_manager_t *clients_manager
)
{
    static uint64_t id_count = 0;

    if (client->team_name == NULL) {
        if (requests_manager_add_to_team(client, clients_manager) == false) {
            log_failure_add_to_team(client, client->team_name);
            client->team_name = NULL;
            return false;
        }
        client->id = id_count;
        id_count++;
        log_success_add_to_team(client);
        return false;
    }
    return true;
}

//TODO: handle errors correctly
/**
* @brief handle the request of the client
* @param client the client that sent the request
* @param clients_manager the clients manager
**/
static void requests_manager_handle_request(client_t *client,
    client_manager_t *clients_manager, map_t *map)
{
    char **args = NULL;

    remove_newline(client->current_request_to_handle);
    if (!requests_manager_client_have_team(client, clients_manager))
        return;
    args = str_array_split(client->current_request_to_handle, " ");
    if (args == NULL || args[0] == NULL)
        return;
    requests_manager_handle_request_on_client_type(
        client, args, clients_manager, map
    );
    requests_manager_free_request_memory(args, client);
}

void requests_manager_handle_requests(
    client_manager_t *clients_manager,
    map_t *map
)
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
                current->client, clients_manager, map
            );
        }
    }
}
