/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** broadcast success log
*/

#include "logs/successes/logs_successes.h"

void log_success_broadcast(const uint64_t id, const char *message)
{
    LOG_SUCCESS("Player %lu broadcasted: %s\n", id, message);
}
