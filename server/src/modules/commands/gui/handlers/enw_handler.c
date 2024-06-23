/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** enw handler
*/

#include "../gui_commands.h"
#include "requests_manager/requests_manager.h"
#include <string.h>

void enw_handler(gui_handler_data_t *data)
{
    char *response = malloc(sizeof(char) * 9 + strlen(data->args[1]) + strlen
        (data->args[2]) + strlen(data->args[3]) + strlen(data->args[4]) + 1);

    snprintf(response, MAX_RESPONSE_SIZE, "enw %s %s %s %s\n",
        data->args[1], data->args[2], data->args[3], data->args[4]);
    client_add_request(data->gui_client->client, response, TO_SEND);
}
