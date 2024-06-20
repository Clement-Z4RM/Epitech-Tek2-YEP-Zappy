/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** sbp.c
*/

#include "../gui_commands.h"

void sbp(client_t *client)
{
    char response[MAX_RESPONSE_SIZE];

    snprintf(response, MAX_RESPONSE_SIZE, "sbp\n");
    client_add_request(client, response, TO_SEND);
}
