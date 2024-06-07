/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** Requests_manager module
*/

#pragma once
#include "../clients_manager/clients_manager.h"

#define HANDLERS_COUNT 1

/** @brief represent the data that will be passed to the handler **/
typedef struct handler_data {
    client_t *client;
    char **args;
    client_manager_t *clients_manager;
} handler_data_t;

/** @brief represent a request handler  **/
typedef struct request_handler {
    const char *command_name;
    void (*handler)(handler_data_t *);
} request_handler_t;

void example_handler(handler_data_t *handler_data)
{
    (void)handler_data;
}

/** @brief  handle a request  **/
extern void requests_manager_handle_request(
    char *request,
    client_t *client,
    client_manager_t *clients_manager
);

/** @brief the list of request handlers **/
static const request_handler_t request_handlers[HANDLERS_COUNT] = {
    {"test", &example_handler}
};
