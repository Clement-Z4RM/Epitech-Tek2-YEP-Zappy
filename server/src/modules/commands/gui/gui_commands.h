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

/**
 * @brief gui_handler_data_t definition for circular dependency
 * with requests manager
 */
typedef struct gui_handler_data_s gui_handler_data_t;

extern void msz(gui_handler_data_t *data);
extern void bct(gui_handler_data_t *data);
