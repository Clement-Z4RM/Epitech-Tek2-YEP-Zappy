/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** Requests_manager module
*/

#pragma once

#include <stddef.h>
#include "clients_manager/clients_manager.h"

/** @brief represent the data that will be passed to the handler **/
typedef struct ai_handler_data_s {
    client_t *client;
    char **args;
    client_manager_t *clients_manager;
} ai_handler_data_t;

/** @brief represent a ai request handler  **/
typedef struct ai_request_handler_s {
    const char *command_name;
    void (*handler)(ai_handler_data_t *);
} ai_request_handler_t;

/** @brief represent the data that will be passed to the handler **/
typedef struct gui_handler_data_s {
    client_t *client;
    char **args;
    client_manager_t *clients_manager;
} gui_handler_data_t;

/** @brief represent a gui request handler  **/
typedef struct gui_request_handler_s {
    const char *command_name;
    void (*handler)(gui_handler_data_t *);
} gui_request_handler_t;

/** @brief  handle clients requests  **/
extern void requests_manager_handle_requests(
    client_manager_t *clients_manager
);

// TODO: Don't put null element at end of below lists

/** @brief the list of ai request handlers **/
static const ai_request_handler_t AI_HANDLERS[] = {0};

#define AI_HANDLERS_COUNT sizeof(AI_HANDLERS) / sizeof(ai_request_handler_t)

/** @brief the list of gui request handlers **/
static const gui_request_handler_t GUI_HANDLERS[] = {0};

#define GUI_HANDLERS_COUNT sizeof(GUI_HANDLERS) / sizeof(gui_request_handler_t)
