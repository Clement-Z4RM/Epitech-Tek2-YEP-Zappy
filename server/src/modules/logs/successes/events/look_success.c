/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** look success log
*/

#include "logs/successes/logs_successes.h"

void log_success_look(const player_t *player)
{
    LOG_SUCCESS("Player %lu looked to %d\n", player->id, player->direction);
}
