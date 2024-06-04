/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** Network module
*/

#include "network.h"

void network_destructor(network_t *network)
{
    if (network->endpoint)
        endpoint_destructor(network->endpoint);
    free(network);
}

network_t *network_constructor(char *ip, int port)
{
    network_t *network = malloc(sizeof(network_t));

    if (network == NULL)
        return NULL;
    network->endpoint = endpoint_constructor(ip, port, SERVER);
    if (network->endpoint == NULL) {
        free(network);
        return NULL;
    }
    network->clients_manager = client_manager_constructor();
    return network;
}
