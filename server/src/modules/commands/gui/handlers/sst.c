/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** sst.c
*/

#include "../gui_commands.h"

void sst(gui_handler_data_t *data)
{
    char *endptr = NULL;
    uint64_t t = strtol(data->args[1], &endptr, 10);
    char response[MAX_RESPONSE_SIZE];

    if (endptr == data->args[1]) {
        sbp(data->gui_client->client);
        log_sst_failure(data->gui_client->client);
        return;
    }
    data->updater->generation_interval = t * 20;
    data->updater->next_generation = data->updater->previous_time +
        data->updater->generation_interval;
    snprintf(response, MAX_RESPONSE_SIZE, "sst %lu\n", t);
    client_add_request(data->gui_client->client, response, TO_SEND);
    log_sst_success(data->gui_client->client);
}
