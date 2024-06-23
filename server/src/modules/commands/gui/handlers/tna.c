/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** tna.c
*/

#include <string.h>
#include "../gui_commands.h"
#include "requests_manager/requests_manager.h"

static void send_team(char *name, client_t *client)
{
    char *response = malloc(MAX_RESPONSE_SIZE);

    if (!response) {
        client_add_request(client, strdup("ko\n"), TO_SEND);
        return;
    }
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
    log_success_tna(data->gui_client->client);
}
