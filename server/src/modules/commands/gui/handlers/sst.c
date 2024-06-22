/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** sst.c
*/

#include <string.h>
#include "../gui_commands.h"

void sst(gui_handler_data_t *data)
{
    char *endptr = NULL;
    time_t t = strtol(data->args[1], &endptr, 10);
    char *response = malloc(MAX_RESPONSE_SIZE);

    if (!response) {
        client_add_request(data->gui_client->client, strdup("ko\n"), TO_SEND);
        return;
    }
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
    log_success_sst(data->gui_client->client, t);
}
