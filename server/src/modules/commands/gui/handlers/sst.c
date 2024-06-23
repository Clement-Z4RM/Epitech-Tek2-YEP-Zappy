/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** sst.c
*/

#include <string.h>
#include "../gui_commands.h"
#include "requests_manager/requests_manager.h"

static void update_updater(updater_t *updater, time_t t)
{
    updater->network->options->freq = t;
    updater->generation_interval = (time_t)(20000 / t);
    if (0 == updater->generation_interval)
        updater->generation_interval = 1;
    updater->next_generation = updater->previous_time +
        updater->generation_interval;
}

void sst(gui_handler_data_t *data)
{
    char *endptr = NULL;
    time_t t = strtol(data->args[1], &endptr, 10);
    char *response = malloc(MAX_RESPONSE_SIZE);

    if (!response) {
        client_add_request(data->gui_client->client, strdup("ko\n"), TO_SEND);
        return;
    }
    if (endptr == data->args[1] || t <= 0) {
        sbp(data->gui_client->client);
        log_sst_failure(data->gui_client->client);
        free(response);
        return;
    }
    update_updater(data->updater, t);
    snprintf(response, MAX_RESPONSE_SIZE, "sst %lu\n", t);
    client_add_request(data->gui_client->client, response, TO_SEND);
    log_success_sst(data->gui_client->client, t);
}
