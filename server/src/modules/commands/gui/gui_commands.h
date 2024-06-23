/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** command msz
*/

#pragma once
#include <stdio.h>
#include "macros.h"
#include "sys/types.h"
#include "responses.h"
#include "coords.h"
#include "logs/logs.h"

#define MAX_DIGITS 21

#define MAX_DIGITS 21

/**
 * @brief gui_handler_data_t definition for circular dependency
 * with requests manager
 */
typedef struct gui_handler_data_s gui_handler_data_t;

/** HANDLERS **/
extern void msz(gui_handler_data_t *data);
extern void bct(gui_handler_data_t *data);
extern void mct(gui_handler_data_t *data);
extern void pin(gui_handler_data_t *data);
extern void ppo(gui_handler_data_t *data);
extern void plv(gui_handler_data_t *data);
extern void sgt(gui_handler_data_t *data);
extern void sst(gui_handler_data_t *data);
extern void tna(gui_handler_data_t *data);
extern void enw_handler(gui_handler_data_t *data);

/** EVENTS **/
extern void plv_event(
    const player_t *player,
    const clients_manager_t *clients_manager
);
extern void pfk(uint64_t id, const clients_manager_t *clients_manager);
extern void pnw(const ai_client_node_t *ai_client,
    const clients_manager_t *clients_manager);
extern void pex(uint64_t id, const clients_manager_t *clients_manager);
extern void pbc(uint64_t id, char *msg,
    const clients_manager_t *clients_manager);
extern void smg(char *msg, const clients_manager_t *clients_manager);
extern void seg(char *team_name, clients_manager_t *clients_manager);
extern void pdi(uint64_t id, clients_manager_t *clients_manager);
extern void sbp(client_t *client);
extern void ebo(const uint64_t egg_id,
    const clients_manager_t *clients_manager);
extern void ppo_event(ai_client_node_t *ai_client, clients_manager_t
    *client_manager);
extern void pdr(
    uint64_t id,
    resource_name_t resource,
    clients_manager_t *clients_manager
);
extern void pgt(
    uint64_t id,
    resource_name_t resource,
    clients_manager_t *client_manager
);
extern void enw(const uint64_t egg_id, const uint64_t player_id,
    const clients_manager_t *clients_manager, const coords_t *coords);
