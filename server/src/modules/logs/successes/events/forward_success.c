/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** forward command success
*/

#include "logs/successes/logs_successes.h"

void log_success_forward(const player_t *player)
{
    LOG_SUCCESS("Player %lu forward to x:%lu y:%lu\n", player->id, player->x,
        player->y);
}
