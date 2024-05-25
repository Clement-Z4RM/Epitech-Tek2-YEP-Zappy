/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** world_height.c
*/

#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include "macros.h"
#include "utilities.h"
#include "../options.h"

bool parse_world_height(options_t *options, UNUSED char *argv[])
{
    bool error = false;

    options->world.y = str_to_num(optarg, 1, LONG_MAX, &error);
    if (error) {
        fprintf(stderr, "%s: Invalid world height\n", optarg);
        return false;
    }
    return true;
}
