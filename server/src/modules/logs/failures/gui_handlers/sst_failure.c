/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** sst_failure.c
*/

#include "../logs_failures.h"

void log_sst_failure(const client_t *client)
{
    const char *ip = inet_ntoa(client->addr->sin_addr);
    const int port = ntohs(client->addr->sin_port);

    LOG_FAILURE("Sst command received from %s:%d failed (bad arguments)\n", ip,
        port);
}
