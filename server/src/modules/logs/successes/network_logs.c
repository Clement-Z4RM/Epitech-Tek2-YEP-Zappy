/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** logs for network
*/
#include "../../client/client.h"
#include "logs_successes.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "arpa/inet.h"

void log_network_client_connected_success(client_t *client)
{
    char *ip = inet_ntoa(client->addr->sin_addr);
    int port = ntohs(client->addr->sin_port);

    LOG_SUCCESS("Client connected: %s:%d\n", ip, port);
}
