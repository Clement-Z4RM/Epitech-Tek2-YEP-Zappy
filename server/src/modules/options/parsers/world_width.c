/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** world_width.c
*/

#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include "macros.h"
#include "utilities.h"
#include "../options.h"

bool parse_world_width(options_t *options, UNUSED char *argv[])
{
    bool error = false;

    options->world.x = str_to_num(optarg, 1, LONG_MAX, &error);
    if (error) {
        fprintf(stderr, "%s: Invalid world width\n", optarg);
        return false;
    }
    return true;
}
