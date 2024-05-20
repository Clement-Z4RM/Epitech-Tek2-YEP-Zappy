/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** client_module
*/

#include "client.h"
#include <stdlib.h>

client_t *client_create(int socket)
{
    client_t *client = malloc(sizeof(client_t));

    if (!client)
        return NULL;
    client->socket = socket;
    return client;
}
