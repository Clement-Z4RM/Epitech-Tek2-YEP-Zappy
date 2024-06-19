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

/** HANDLERS **/
extern void msz(gui_handler_data_t *data);
extern void bct(gui_handler_data_t *data);
extern void mct(gui_handler_data_t *data);

/** EVENTS **/
extern void plv(const ai_client_node_t *ai_client);
