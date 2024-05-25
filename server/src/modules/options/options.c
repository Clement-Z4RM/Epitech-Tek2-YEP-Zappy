/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** options.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
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

/**
 * @brief Options structure destructor
 *
 * @param options The options structure to destroy
 */
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
 * @brief Parse the program options
 *
 * @param argc Program arguments count
 * @param argv Program arguments vector
 *
 * @return The program options as an options_t pointer,
 * or NULL if an error occurred
 *
 * @warning The returned pointer is allocated
 * and must be destroyed using options_destructor
 */
options_t *parse_options(int argc, char *argv[])
{
    options_t *options = options_constructor();
    int opt;

    if (!options)
        return NULL;
    for (opt = NEXT_OPT(argc, argv); -1 != opt; opt = NEXT_OPT(argc, argv)) {
        if (OPTION_PARSERS[opt].argument_required && '-' == optarg[0]) {
            fprintf(stderr, "%s: option requires an argument -- '%c'\n",
                    *argv, opt);
            options_destructor(options);
            return NULL;
        }
        if (!OPTION_PARSERS[opt].parser(options, argv)) {
            options_destructor(options);
            return NULL;
        }
    }
    return options;
}
