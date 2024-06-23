/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** ppo_success.c
*/

#include "../logs_successes.h"

void log_success_ppo(const client_t *client, const player_t *player)
{
    const char *ip = inet_ntoa(client->addr->sin_addr);
    const int port = ntohs(client->addr->sin_port);

    LOG_SUCCESS("Ppo command received from %s:%d executed successfully, "
    "informations of the player getted: x:%lu y:%lu o:%d \n", ip,
        port, player->x, player->y, player->direction);
}
