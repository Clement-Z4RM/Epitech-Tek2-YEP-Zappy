/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** sgt.c
*/

#include <stdlib.h>
#include <string.h>
#include "../gui_commands.h"
#include "requests_manager/requests_manager.h"

void sgt(gui_handler_data_t *data)
{
    char *response = malloc(MAX_RESPONSE_SIZE);

    if (!response) {
        client_add_request(data->gui_client->client, strdup("ko\n"), TO_SEND);
        return;
    }
    snprintf(response, MAX_RESPONSE_SIZE, "sgt %lu\n",
        data->updater->network->options->freq
    );
    client_add_request(data->gui_client->client, response, TO_SEND);
    log_success_sgt(data->gui_client->client);
}
