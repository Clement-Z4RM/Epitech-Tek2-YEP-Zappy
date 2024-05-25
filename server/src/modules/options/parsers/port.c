/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** port.c
*/

#include <unistd.h>
#include <stdio.h>
#include "macros.h"
#include "utilities.h"
#include "../options.h"

bool parse_port(options_t *options, UNUSED char *argv[])
{
    int port = str_to_port(optarg);

    if (ERROR == port) {
        fprintf(stderr, "%s: Invalid port\n", optarg);
        return false;
    }
    options->port = port;
    return true;
}
