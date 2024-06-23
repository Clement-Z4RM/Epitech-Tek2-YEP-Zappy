/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** logs for successes fork
*/

#include "../logs_successes.h"

void log_success_fork(const ai_client_node_t *ai_client)
{
    LOG_SUCCESS("Fork from player %lu executed at position %lu %lu\n",
        ai_client->player.id,
        ai_client->player.x,
        ai_client->player.y
    );
}
