/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** logs failures
*/

#pragma once
#include "../logs_colors.h"
#include "stdio.h"
#include "client/client.h"
#include "netinet/in.h"
#include "arpa/inet.h"

/** @brief macro to print [ERROR] in red
 * directly before the rest of the log**/
#define LOG_FAILURE(...) printf(RED "[ERROR] " RESET __VA_ARGS__)

extern void log_failure_request_no_handler(const client_t *client);
extern void log_failure_null_request(const client_t *client);
extern void log_failure_team_full(const char *team_name);
extern void log_failure_add_to_team(client_t *client, const char *team_name);
extern void log_failure_init_team(const char *team_name);

//gui
extern void log_sst_failure(const client_t *client);
