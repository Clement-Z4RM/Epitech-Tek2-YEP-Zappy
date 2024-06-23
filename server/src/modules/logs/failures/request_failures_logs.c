/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** logs for network
*/

#include "logs_failures.h"
#include "netinet/in.h"
#include "arpa/inet.h"

/** @brief log a failure message when a client request dosn't have handler
    @param client the client that sent the request **/
void log_failure_request_no_handler(const client_t *client)
{
    char *ip = inet_ntoa(client->addr->sin_addr);
    int port = ntohs(client->addr->sin_port);

    LOG_FAILURE("Client request has no handler: %s:%d"
                " | request: %s\n", ip, port,
                client->current_request_to_handle
    );
}

void log_failure_null_request(const client_t *client)
{
    char *ip = inet_ntoa(client->addr->sin_addr);
    int port = ntohs(client->addr->sin_port);

    LOG_FAILURE("Client request to send is NULL: %s:%d\n", ip, port);
}
