/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** inventory.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "requests_manager/requests_manager.h"
#include "inventory.h"

static void fill_inventory(char *inventory, ai_client_node_t *client)
{
    snprintf(
        inventory,
        INVENTORY_SIZE,
        "["
        "food %lu,"
        " linemate %lu,"
        " deraumere %lu,"
        " sibur %lu,"
        " mendiane %lu,"
        " phiras %lu,"
        " thystame %lu"
        "]\n",
        (u_int64_t)client->player.life_span,
        client->player.resources[RN_LINEMATE],
        client->player.resources[RN_DERAUMERE],
        client->player.resources[RN_SIBUR],
        client->player.resources[RN_MENDIANE],
        client->player.resources[RN_PHIRAS],
        client->player.resources[RN_THYSTAME]
    );
}

static void inventory_updater(
    ai_client_node_t *client,
    UNUSED updater_t *updater,
    void *arg
)
{
    client->client->busy = false;
    fill_inventory((char *)arg, client);
    client_add_request(client->client, (char *)arg, TO_SEND);
}

/**
 * @brief Inventory command.
 * Send to the player his inventory
 * (its objects and how much time it has left to live).
 *
 * This command takes 1 tick to execute.
 *
 * @param data The structure containing all needed informations.
 */
void inventory(ai_handler_data_t *data)
{
    char *inventory = malloc(INVENTORY_SIZE);
    command_updater_data_t updater_data;

    if (!inventory) {
        client_add_request(data->client->client, strdup("ko\n"), TO_SEND);
        return;
    }
    updater_data.executed_at = data->updater->elapsed;
    updater_data.time = 1;
    updater_data.client = data->client;
    updater_data.id = data->client->player.id;
    updater_data.arg = (void *)inventory;
    data->client->client->busy = true;
    updater_add_command(data->updater, &updater_data, inventory_updater);
}
