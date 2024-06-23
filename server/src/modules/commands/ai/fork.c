/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** fork.c
*/

#include <string.h>
#include "requests_manager/requests_manager.h"

static void fork_updater(
    ai_client_node_t *client,
    updater_t *updater,
    UNUSED void *arg
)
{
    team_node_t *team = clients_manager_get_team_by_client(
        updater->network->clients_manager,
        client
    );

    client->client->busy = false;
    if (!team) {
        client_add_request(client->client, strdup("ko\n"), TO_SEND);
        return;
    }
    if (!spawn_egg(updater->map, &team, client->player.x, client->player.y)) {
        client_add_request(client->client, strdup("ko\n"), TO_SEND);
        return;
    }
    client_add_request(client->client, strdup("ok\n"), TO_SEND);
}

/**
 * @brief Fork command.
 * Reproduce a player, leading to the production of an egg.
 *
 * This operation authorizes a new client to be connected.
 *
 * This command takes 42 ticks to execute.
 *
 * @param data The structure containing all needed informations.
 */
void fork_command(ai_handler_data_t *data)
{
    command_updater_data_t updater_data = {
        data->updater->elapsed,
        42,
        data->client,
        NULL
    };

    data->client->client->busy = true;
    updater_add_command(data->updater, &updater_data, fork_updater);
}
