/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** Requests_manager module
*/

#include "requests_manager.h"
#include "stdlib.h"
#include <string.h>
#include "../../include/utilities.h"

static char **request_manager_parse_args(char *request)
{
    char **args = str_array_split(request, " ");

    return args;
}

void request_manager_handle_request(char *request, client_t *client,
    client_manager_t *clients_manager)
{
    char **args = request_manager_parse_args(request);
    handler_data_t handler_data = {client, args, clients_manager};

    for (int i = 0; i < HANDLERS_COUNT; i++) {
        if (strcmp(request_handlers[i].command_name, args[0]) == 0) {
            request_handlers[i].handler(&handler_data);
            break;
        }
    }
    free(args);
}
