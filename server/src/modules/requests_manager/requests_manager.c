/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** Requests_manager module
*/

#include <stdlib.h>
#include <string.h>
#include "utilities.h"
#include "logs/failures/logs_failures.h"
#include "logs/successes/logs_successes.h"
#include "requests_manager.h"

/**
* @brief check if the client has a team name
* @param client the client to check
* @param manager the clients manager
 * @param map the map
* @return bool true if the client has a team name, false otherwise
**/
static bool add_to_team(
    client_t *client,
    clients_manager_t *manager,
    map_t *map
)
{
    client->team_name = client->current_request_to_handle;
    client->current_request_to_handle = NULL;
    if (strcmp(client->team_name, "GRAPHIC") == 0) {
        return clients_manager_add(manager, client, GUI);
    }
    if (clients_manager_add_to_team(
        manager,
        client,
        client->team_name,
        map
    ) == false) {
        return false;
    }
    return true;
}

/**
* @brief freeing memory of the currently handled request
* @param args parsed args of the request
* @param client the client that sent the request
**/
static void free_request_memory(char **args, client_t *client)
{
    if (client) {
        if (client->current_request_to_handle)
            free(client->current_request_to_handle);
        client->current_request_to_handle = NULL;
    }
    free_double_tab(args);
}

static void handle_ai_request(
    char **args,
    ai_client_node_t *client,
    clients_manager_t *manager,
    updater_t *updater
)
{
    ai_handler_data_t handler_data = {client, args, manager, updater};

    for (size_t i = 0; i < AI_HANDLERS_COUNT; i++) {
        if (AI_HANDLERS[i].command_name == NULL)
            continue;
        if (strcmp(AI_HANDLERS[i].command_name, args[0]) == 0) {
            AI_HANDLERS[i].handler(&handler_data);
            return;
        }
    }
    log_failure_request_no_handler(client->client);
}

static void handle_gui_request(
    char **args,
    gui_client_node_t *client,
    updater_t *updater
)
{
    gui_handler_data_t handler_data = {client, args, updater};

    for (size_t i = 0; i < GUI_HANDLERS_COUNT; i++) {
        if (GUI_HANDLERS[i].command_name == NULL)
            continue;
        if (strcmp(GUI_HANDLERS[i].command_name, args[0]) == 0) {
            GUI_HANDLERS[i].handler(&handler_data);
            return;
        }
    }
    client_add_request(client->client, strdup("suc\n"), TO_SEND);
    log_failure_request_no_handler(client->client);
}

static bool client_has_team(
    client_t *client,
    clients_manager_t *manager,
    map_t *map
)
{
    if (client->team_name == NULL) {
        if (add_to_team(client, manager, map) == false) {
            client_add_request(client, strdup("ko\n"), TO_SEND);
            log_failure_add_to_team(client, client->team_name);
            free(client->team_name);
            client->team_name = NULL;
            return false;
        }
        log_success_add_to_team(client);
    }
    return true;
}

/**
* @brief parse the arguments of the request
 *
* @param client the client that sent the request
* @param manager the clients manager
 * @param args a pointer to a char array that will contain the parsed args
**/
static bool parse_args(client_t *client, char ***args)
{
    if (!client || !client->current_request_to_handle)
        return false;
    remove_newline(client->current_request_to_handle);
    *args = str_array_split(client->current_request_to_handle, " ");
    if (*args == NULL || (*args)[0] == NULL)
        return false;
    return true;
}

static client_t *get_client(client_node_t *current)
{
    client_t *client = current->client;
    char *request = NULL;

    if (client->current_request_to_handle == NULL && !client->busy) {
        request = client_popback_request(client, TO_HANDLE);
        client->current_request_to_handle = request;
        return client;
    }
    return NULL;
}

static void handle_none_clients_requests(
    clients_manager_t *manager,
    map_t *map
)
{
    client_node_t *current = NULL;
    char *request = NULL;
    client_t *client = NULL;

    for (current = SLIST_FIRST(&manager->clients_list); current;
        current = SLIST_NEXT(current, next)) {
        client = current->client;
        if (NONE == client->type &&
            client->current_request_to_handle == NULL
        ) {
            request = client_popback_request(client, TO_HANDLE);
            client->current_request_to_handle = request;
        }
        if (client->current_request_to_handle == NULL)
            continue;
        remove_newline(client->current_request_to_handle);
        client_has_team(client, manager, map);
        free_request_memory(NULL, client);
    }
}

static void requests_manager_handle_team_requests(
    clients_manager_t *manager,
    updater_t *updater,
    team_node_t *team_current
)
{
    ai_client_node_t *ai_current = NULL;
    client_t *client = NULL;
    char **args = NULL;

    for (ai_current = SLIST_FIRST(&team_current->ai_clients);
        ai_current; ai_current = SLIST_NEXT(ai_current, next)) {
        client = get_client((client_node_t *)ai_current);
        if (parse_args(client, &args))
            handle_ai_request(args, ai_current, manager, updater);
        free_request_memory(args, client);
    }
}

void requests_manager_handle_requests(
    clients_manager_t *manager,
    updater_t *updater
)
{
    gui_client_node_t *gui_current = NULL;
    team_node_t *team_current = NULL;
    client_t *client = NULL;
    char **args = NULL;

    handle_none_clients_requests(manager, updater->map);
    for (team_current = SLIST_FIRST(&manager->team_list); team_current;
        team_current = SLIST_NEXT(team_current, next)) {
        requests_manager_handle_team_requests(manager, updater, team_current);
    }
    SLIST_FOREACH(gui_current, &manager->gui_clients_list, next) {
        client = get_client((client_node_t *)gui_current);
        if (parse_args(client, &args))
            handle_gui_request(args, gui_current, updater);
        free_request_memory(args, client);
    }
}
