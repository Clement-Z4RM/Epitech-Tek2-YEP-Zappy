/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** sgt.c
*/

#include "../gui_commands.h"

void sgt(gui_handler_data_t *data)
{
    char response[MAX_RESPONSE_SIZE];

    snprintf(response, MAX_RESPONSE_SIZE, "sgt %lu\n",
        1 / data->updater->network->options->freq
    );
    client_add_request(data->gui_client->client, response, TO_SEND);
    log_sgt_success(data->gui_client->client);
}
