/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** set success log
*/

#include "logs/successes/logs_successes.h"
#include "resource/resource.h"

void log_success_set(const uint64_t id, resource_name_t resource)
{
    LOG_SUCCESS("Player %lu set down: %s\n", id,
        RESOURCE_NAMES[resource]);
}
