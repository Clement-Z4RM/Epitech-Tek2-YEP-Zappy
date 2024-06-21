/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** broadcast.c
*/

#include "ai_commands.h"
#include "math.h"

static ai_client_node_t **get_ai_node_tab(clients_manager_t *clients_manager)
{
    team_node_t *current_team = NULL;
    ai_client_node_t *current_ai = NULL;
    ai_client_node_t **ai_node_tab = malloc(
        sizeof(ai_client_node_t *) * clients_manager->nb_ai_clients + 1
    );
    int i = 0;

    SLIST_FOREACH(current_team, &clients_manager->team_list, next)
    {
        SLIST_FOREACH(current_ai, &current_team->ai_clients, next)
        {
            ai_node_tab[i] = current_ai;
            i++;
        }
    }
    return ai_node_tab;
}

static int get_direction_tile(player_t *emitter, player_t *receiver)
{

}

void broadcast(ai_handler_data_t *data)
{
    char *msg = data->args[1];
    ai_client_node_t **ai_node_tab = NULL;

    if (msg == NULL)
        return;
    ai_node_tab = get_ai_node_tab(data->clients_manager);
    free(ai_node_tab);
}