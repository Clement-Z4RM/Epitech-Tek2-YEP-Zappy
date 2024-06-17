/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** logs for successes
*/

#include "logs_successes.h"
#include "../../client/client.h"
#include "netinet/in.h"
#include "arpa/inet.h"

void log_success_add_to_team(client_t *client)
{
    char *ip = inet_ntoa(client->addr->sin_addr);
    int port = ntohs(client->addr->sin_port);

    LOG_SUCCESS("Client joined team: %s:%d | team: %s\n", ip, port,
                client->team_name);
}
