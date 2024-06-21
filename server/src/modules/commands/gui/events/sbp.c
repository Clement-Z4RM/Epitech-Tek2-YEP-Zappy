/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** sbp.c
*/

#include <string.h>
#include "../gui_commands.h"

void sbp(client_t *client)
{
    char *response = malloc(MAX_RESPONSE_SIZE);

    if (!response) {
        client_add_request(client, strdup("ok\n"), TO_SEND);
        return;
    }
    snprintf(response, MAX_RESPONSE_SIZE, "sbp\n");
    client_add_request(client, response, TO_SEND);
}
