/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** Requests_manager module
*/

#pragma once
#include "../clients_manager/clients_manager.h"

#define HANDLERS_COUNT 1

typedef struct handler_data {
    client_t *client;
    char **args;
    client_manager_t *clients_manager;
} handler_data_t;

typedef struct request_handler {
    const char *command_name;
    void (*handler)(handler_data_t *);
} request_handler_t;

static const request_handler_t request_handlers[HANDLERS_COUNT] = {0};

extern void request_manager_handle_request(
    char *request,
    client_t *client,
    client_manager_t *clients_manager
);
