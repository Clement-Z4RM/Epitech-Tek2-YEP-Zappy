/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** log for pdi command
*/

#include "logs/successes/logs_successes.h"

void log_success_pdi(const uint64_t id)
{
    LOG_SUCCESS("Player died: %lu\n", id);
}
