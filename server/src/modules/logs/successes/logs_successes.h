/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** logs successes
*/

#pragma once
#include "stdio.h"
#include "../logs_colors.h"
#include "../../client/client.h"

/** @brief macro to print [SUCCESS] in green
 * directly before the rest of the log**/
#define LOG_SUCCESS(...) printf(GREEN "[SUCCESS] " RESET __VA_ARGS__)

/** @brief log a success message when a client is connected **/
extern void log_success_network_client_connected(client_t *client);

/** @brief log a sucess message when a client join a team **/
extern void log_success_add_to_team(client_t *client);

extern void log_success_init_team(const char *team_name);
