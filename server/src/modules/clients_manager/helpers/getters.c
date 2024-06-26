/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** clients_manager module getters
*/

#include <stddef.h>
#include <string.h>
#include "../clients_manager.h"

ai_client_node_t *clients_manager_get_ai_by_id(
    clients_manager_t *manager,
    uint64_t id
)
{
    ai_client_node_t *node = NULL;
    team_node_t *current_team = NULL;

    SLIST_FOREACH(current_team, &manager->team_list, next) {
        SLIST_FOREACH(node, &current_team->ai_clients, next) {
            if (node->player.id == id)
                return node;
        }
    }
    return NULL;
}

team_node_t *clients_manager_get_team_by_client(
    clients_manager_t *manager,
    ai_client_node_t *client
)
{
    team_node_t *team;

    SLIST_FOREACH(team, &manager->team_list, next)
        if (team->name && client->client->team_name &&
            !strcmp(team->name, client->client->team_name))
            return team;
    return NULL;
}
