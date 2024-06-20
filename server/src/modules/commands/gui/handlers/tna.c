/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** tna.c
*/

#include "../gui_commands.h"
#include "logs/successes/logs_successes.h"

static void send_team(char *name, client_t *client)
{
    char response[MAX_RESPONSE_SIZE];

    snprintf(response, MAX_RESPONSE_SIZE, "tna %s\n", name);
    client_add_request(client, response, TO_SEND);
}

void tna(gui_handler_data_t *data)
{
    team_node_t *current_team = NULL;

    SLIST_FOREACH(current_team,
        &data->updater->network->clients_manager->team_list,
        next
    )
    {
        send_team(current_team->name, data->gui_client->client);
    }
    log_tna_success(data->gui_client->client);
}
