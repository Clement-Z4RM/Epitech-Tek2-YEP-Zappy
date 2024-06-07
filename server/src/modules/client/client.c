/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** client_module
*/

#include "client.h"
#include <stdlib.h>
#include <stdio.h>

void client_destroy(client_t *client)
{
    if (client->team_name)
        free(client->team_name);
    free(client);
}

client_t *client_create(int socket)
{
    client_t *client = malloc(sizeof(client_t));

    if (!client) {
        perror("malloc");
        return NULL;
    }
    client->socket = socket;
    client->team_name = NULL;
    return client;
}
