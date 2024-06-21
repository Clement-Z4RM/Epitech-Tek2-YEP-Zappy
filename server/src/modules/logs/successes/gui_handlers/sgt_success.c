/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** sgt_success.cs
*/

#include "../logs_successes.h"

void log_success_sgt(const client_t *client)
{
    const char *ip = inet_ntoa(client->addr->sin_addr);
    const int port = ntohs(client->addr->sin_port);

    LOG_SUCCESS("Sgt command received from %s:%d executed successfully\n", ip,
        port);
}
