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
#include "netinet/in.h"
#include "arpa/inet.h"
#include "player/player.h"
#include "clients_manager/clients_manager.h"

/** @brief macro to print [SUCCESS] in green
 * directly before the rest of the log**/
#define LOG_SUCCESS(...) printf(GREEN "[SUCCESS] " RESET __VA_ARGS__)

/** @brief log a success message when a client is connected **/
extern void log_success_network_client_connected(client_t *client);

/** @brief log a sucess message when a client join a team **/
extern void log_success_add_to_team(client_t *client);

extern void log_success_init_team(const char *team_name);

//gui handlers
extern void log_success_tna(const client_t *client);
extern void log_success_sst(const client_t *client, uint64_t t);
extern void log_success_sgt(const client_t *client);
extern void log_success_ppo(const client_t *client, const player_t *player);

//events
extern void log_success_forward(const player_t *player);
extern void log_success_pdi(const uint64_t id);
extern void log_success_broadcast(const uint64_t id, const char *message);
extern void log_success_look(const player_t *player);
extern void log_success_turn(const player_t *player);
extern void log_success_set(const uint64_t id, resource_name_t resource);
extern void log_success_take(const uint64_t id, resource_name_t resource);
