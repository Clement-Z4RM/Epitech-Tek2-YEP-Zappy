/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** logs successes
*/

#pragma once
#include "stdio.h"
#include "../logs_colors.h"

/** @brief macro to print [SUCCESS] in green
 * directly before the rest of the log**/
#define LOG_SUCCESS(...) printf(GREEN "[SUCCESS] " RESET __VA_ARGS__)

/** @brief log a success message when a client is connected **/
void log_network_client_connected_success(client_t *client);
