/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** command msz
*/

#pragma once
#include <stdio.h>
#include "macros.h"
#include "requests_manager/requests_manager.h"
#include "sys/types.h"
#include "responses.h"

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

/** EVENTS **/
extern void plv(const player_t *player,
    const clients_manager_t *clients_manager);
extern void pfk(uint64_t id, const clients_manager_t *clients_manager);
extern void pnw(const ai_client_node_t *ai_client,
    const clients_manager_t *clients_manager);
extern void pex(uint64_t id, const clients_manager_t *clients_manager);
extern void pbc(uint64_t id, char *msg,
    const clients_manager_t *clients_manager);
