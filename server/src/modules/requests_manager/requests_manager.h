/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** Requests_manager module
*/

#pragma once
#include "../clients_manager/clients_manager.h"

#define AI_HANDLERS_COUNT 1
#define GUI_HANDLERS_COUNT 1

/** @brief represent the data that will be passed to the handler **/
typedef struct ai_handler_data {
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
typedef struct gui_request_handler {
    const char *command_name;
    void (*handler)(gui_handler_data_t *);
} gui_request_handler_t;

/** @brief  handle clients requests  **/
extern void requests_manager_handle_requests(
    client_manager_t *clients_manager
);

/** @brief the list of ai request handlers **/
static const ai_request_handler_t
ai_request_handlers[AI_HANDLERS_COUNT] = {0};

/** @brief the list of gui request handlers **/
static const gui_request_handler_t
gui_request_handlers[GUI_HANDLERS_COUNT] = {0};
