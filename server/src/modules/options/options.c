/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** options.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "options.h"

static options_t *options_constructor(void)
{
    options_t *options = malloc(sizeof(options_t));

    if (!options)
        return NULL;
    memset(options, 0, sizeof(options_t));
    SLIST_INIT(&options->teams);
    return options;
}

void options_destructor(options_t *options)
{
    team_name_t *team_name;

    if (!options)
        return;
    while (!SLIST_EMPTY(&options->teams)) {
        team_name = SLIST_FIRST(&options->teams);
        SLIST_REMOVE_HEAD(&options->teams, next);
        free(team_name);
    }
    free(options);
}

/**
 * @param argc
 * @param argv
 * @return
 */
options_t *parse_options(int argc, char *argv[])
{
    options_t *options = options_constructor();
    int opt;

    if (!options)
        return NULL;
    for (opt = NEXT_OPT(argc, argv); -1 != opt; opt = NEXT_OPT(argc, argv)) {
        if ('?' == opt) {
            options_destructor(options);
            return NULL;
        }
        if (1 == opt) {
            // TODO
        }
    }
    return options;
}
