/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** module used to manage clients
*/

#include <sys/queue.h>
#include <stdlib.h>
#include <string.h>
#include "clients_manager.h"
#include <stdio.h>

static void send_gui_default_events(client_t *client, clients_manager_t
    *manager)
{
    team_node_t *team_current = NULL;
    ai_client_node_t *ai_current = NULL;
    char ppo_request[16];

    client_add_request(client, strdup("msz\n"), TO_HANDLE);
    client_add_request(client, strdup("sgt\n"), TO_HANDLE);
    client_add_request(client, strdup("mct\n"), TO_HANDLE);
    client_add_request(client, strdup("tna\n"), TO_HANDLE);
    SLIST_FOREACH(team_current, &manager->team_list, next) {
        SLIST_FOREACH(ai_current, &team_current->ai_clients, next) {
            snprintf(ppo_request, 16, "ppo %ld\n", ai_current->player.id);
            client_add_request(client, strdup(ppo_request), TO_HANDLE);
            send_default_eggs(team_current, client);
        }
    }
}

static bool add_gui(clients_manager_t *manager, client_t *client)
{
    gui_client_node_t *new_node = malloc(sizeof(gui_client_node_t));

    if (new_node == NULL)
        return false;
    new_node->client = client;
    SLIST_INSERT_HEAD(&manager->gui_clients_list, new_node, next);
    manager->nb_gui_clients++;
    send_gui_default_events(client, manager);
    return true;
}

bool clients_manager_add(
    clients_manager_t *manager,
    client_t *client,
    const client_type_t type
)
{
    client_node_t *new_node = NULL;
    bool state = true;

    client->type = type;
    if (type == NONE) {
        new_node = malloc(sizeof(client_node_t));
        if (new_node == NULL)
            return false;
        new_node->client = client;
        SLIST_INSERT_HEAD(&manager->clients_list, new_node, next);
        manager->nb_clients++;
    } else if (type == GUI) {
        state = add_gui(manager, client);
    }
    return state;
}

static void clients_manager_remove_gui(clients_manager_t *manager, client_t
    *client)
{
    gui_client_node_t *current = NULL;
    gui_client_node_t *tmp = NULL;

    for (current = SLIST_FIRST(&manager->gui_clients_list); current; current
    = SLIST_NEXT(current, next)) {
        if (current->client == client) {
            tmp = current;
            break;
        }
    }
    if (tmp) {
        SLIST_REMOVE(&manager->gui_clients_list, tmp, gui_client_node_s, next);
        client_destructor(tmp->client);
        free(tmp);
        manager->nb_gui_clients--;
    }
}

static bool check_ai(client_t *client, team_node_t *team_current)
{
    ai_client_node_t *ai_current = NULL;

    SLIST_FOREACH(ai_current, &team_current->ai_clients, next) {
        if (ai_current->client == client) {
            SLIST_REMOVE(
                &team_current->ai_clients, ai_current,
                ai_client_node_s, next
            );
            free(ai_current);
            return true;
        }
    }
    return false;
}

void clients_manager_remove_ai(clients_manager_t *manager, client_t
    *client)
{
    team_node_t *team_current = NULL;

    for (team_current = SLIST_FIRST(&manager->team_list); team_current;
        team_current = SLIST_NEXT(team_current, next)) {
        if (check_ai(client, team_current)) {
            team_current->nb_clients--;
            manager->nb_ai_clients--;
            break;
        }
    }
}

void clients_manager_remove(clients_manager_t *manager, client_t *client)
{
    client_node_t *current = NULL;
    client_node_t *tmp = NULL;

    for (current = SLIST_FIRST(&manager->clients_list); current;
        current = SLIST_NEXT(current, next)) {
        if (current->client == client) {
            tmp = current;
            break;
        }
    }
    if (tmp) {
        SLIST_REMOVE(&manager->clients_list, tmp, client_node_s, next);
        client_destructor(tmp->client);
        free(tmp);
        manager->nb_clients--;
    }
    if (client->type == GUI)
        clients_manager_remove_gui(manager, client);
    else if (client->type == AI)
        clients_manager_remove_ai(manager, client);
}

static void clients_manager_teams_destructor(clients_manager_t *manager)
{
    team_node_t *team_current = NULL;

    while (!SLIST_EMPTY(&manager->team_list)) {
        team_current = SLIST_FIRST(&manager->team_list);
        SLIST_REMOVE_HEAD(&manager->team_list, next);
        clients_manager_team_destructor(team_current);
    }
}

void clients_manager_destructor(clients_manager_t *manager)
{
    client_node_t *current = NULL;
    gui_client_node_t *gui_current = NULL;

    while (!SLIST_EMPTY(&manager->clients_list)) {
        current = SLIST_FIRST(&manager->clients_list);
        SLIST_REMOVE_HEAD(&manager->clients_list, next);
        client_destructor(current->client);
        free(current);
    }
    while (!SLIST_EMPTY(&manager->gui_clients_list)) {
        gui_current = SLIST_FIRST(&manager->gui_clients_list);
        SLIST_REMOVE_HEAD(&manager->gui_clients_list, next);
        client_destructor(gui_current->client);
        free(gui_current);
    }
    clients_manager_teams_destructor(manager);
    free(manager);
}

clients_manager_t *clients_manager_constructor(options_t *options, map_t *map)
{
    clients_manager_t *manager = malloc(sizeof(clients_manager_t));

    if (manager == NULL)
        return NULL;
    SLIST_INIT(&manager->clients_list);
    SLIST_INIT(&manager->gui_clients_list);
    SLIST_INIT(&manager->team_list);
    manager->nb_clients = 0;
    manager->nb_gui_clients = 0;
    manager->nb_teams = 0;
    manager->nb_ai_clients = 0;
    manager->is_game_started = false;
    clients_manager_init_teams(manager, &options->teams);
    if (!client_manager_init_eggs(manager, options, map)) {
        clients_manager_destructor(manager);
        return NULL;
    }
    return manager;
}
