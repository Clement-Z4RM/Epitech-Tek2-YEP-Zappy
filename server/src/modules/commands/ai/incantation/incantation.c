/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** incantation.c
*/

#include <string.h>
#include "incantation.h"

static void incantation_updater(
    UNUSED ai_client_node_t *client,
    UNUSED updater_t *updater,
    UNUSED char *arg
)
{
}

/**
 * @brief Incantation command.
 * Start an incantation (elevation ritual).
 *
 * This command takes 300 ticks to execute.
 *
 * @param data The structure containing all needed informations.
 */
void incantation(ai_handler_data_t *data)
{
    command_updater_data_t updater_data = {
        data->updater->elapsed,
        300,
        data->client,
        NULL
    };
    incantation_t *incantation = initiate_incantation(data);

    if (!incantation) {
        client_add_request(data->client->client, strdup("ko\n"), TO_SEND);
        return;
    }
    updater_add_command(data->updater, &updater_data, incantation_updater);
}
