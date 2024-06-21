/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** sst_success.c
*/

#include "../logs_successes.h"

void log_success_sst(const client_t *client, uint64_t t)
{
    const char *ip = inet_ntoa(client->addr->sin_addr);
    const int port = ntohs(client->addr->sin_port);

    LOG_SUCCESS("Sst command received from %s:%d executed successfully, "
    "new time unit: %lu\n", ip, port, t);
}
