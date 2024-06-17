/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** logs for network
*/

#include "logs_failures.h"
#include "netinet/in.h"
#include "arpa/inet.h"

void log_failure_add_to_team(client_t *client, const char *team_name)
{
    char *ip = inet_ntoa(client->addr->sin_addr);
    int port = ntohs(client->addr->sin_port);

    LOG_FAILURE("Client failed to join team: %s:%d | team: %s\n", ip, port,
                team_name);
}

void log_failure_team_full(const char *team_name)
{
    LOG_FAILURE("Team is full: %s\n", team_name);
}
