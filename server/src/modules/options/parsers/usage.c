/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** usage.c
*/

#include "macros.h"
#include "../options.h"

bool parse_usage(options_t *options, UNUSED char *argv[])
{
    options->usage = true;
    return true;
}
