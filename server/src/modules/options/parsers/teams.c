/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** teams.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../options.h"

static bool insert_team(
    options_t *options,
    team_name_t **team,
    const char *team_name
)
{
    team_name_t *prev = *team;

    *team = malloc(sizeof(team_name_t));
    if (!*team) {
        perror("malloc");
        return false;
    }
    (*team)->name = team_name;
    if (!prev)
        SLIST_INSERT_HEAD(&options->teams, *team, next);
    else
        SLIST_INSERT_AFTER(prev, *team, next);
    return true;
}

bool parse_teams(options_t *options, char *argv[])
{
    team_name_t *team = NULL;

    if (!insert_team(options, &team, optarg))
        return false;
    for (; argv[optind] && '-' != argv[optind][0]; ++optind)
        if (!insert_team(options, &team, argv[optind]))
            return false;
    if (SLIST_EMPTY(&options->teams)) {
        fprintf(stderr, "At least one team must be specified\n");
        return false;
    }
    return true;
}
