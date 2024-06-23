/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** take success log
*/

#include "logs/successes/logs_successes.h"

void log_success_take(const uint64_t id, resource_name_t resource)
{
    LOG_SUCCESS("Player %lu took: %s\n", id, RESOURCE_NAMES[resource]);
}
