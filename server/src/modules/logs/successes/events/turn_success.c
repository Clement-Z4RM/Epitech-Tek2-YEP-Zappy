/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** turn success log
*/

#include "logs/successes/logs_successes.h"

void log_success_turn(const player_t *player)
{
    LOG_SUCCESS("Player %lu turned to %d\n", player->id, player->direction);
}
