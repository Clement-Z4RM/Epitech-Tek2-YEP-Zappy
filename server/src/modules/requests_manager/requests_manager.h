/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** Requests_manager module
*/

#pragma once

#include <stddef.h>
#include "clients_manager/clients_manager.h"
#include "commands/commands.h"
#include "../updater/updater.h"

/** @brief represent the data that will be passed to the handler **/
typedef struct ai_handler_data_s {
    ai_client_node_t *client;
    char **args;
    clients_manager_t *clients_manager;
    updater_t *updater;
} ai_handler_data_t;

/** @brief represent a ai request handler  **/
typedef struct ai_request_handler_s {
    const char *command_name;
    void (*handler)(ai_handler_data_t *);
} ai_request_handler_t;

/** @brief represent the data that will be passed to the handler **/
typedef struct gui_handler_data_s {
    gui_client_node_t *gui_client;
    char **args;
    updater_t *updater;
} gui_handler_data_t;

/** @brief represent a gui request handler  **/
typedef struct gui_request_handler_s {
    const char *command_name;
    void (*handler)(gui_handler_data_t *);
} gui_request_handler_t;

/** @brief  handle clients requests  **/
extern void requests_manager_handle_requests(
    clients_manager_t *manager,
    updater_t
    *updater
);

// TODO: Don't put null element at end of below lists

/** @brief the list of ai request handlers **/
static const ai_request_handler_t AI_HANDLERS[] = {
    {"Forward", forward},
    {"Right", right},
    {"Left", left},
    {"Look", look},
    {"Inventory", inventory},
    {"Broadcast", broadcast},
    {"Connect_nbr", connect_nbr},
    {"Fork", fork_command},
    {"Take", take},
    {"Set", set},
    {"Incantation", incantation}
};

#define AI_HANDLERS_COUNT sizeof(AI_HANDLERS) / sizeof(ai_request_handler_t)

/** @brief the list of gui request handlers **/
static const gui_request_handler_t GUI_HANDLERS[] = {0};

#define GUI_HANDLERS_COUNT sizeof(GUI_HANDLERS) / sizeof(gui_request_handler_t)
