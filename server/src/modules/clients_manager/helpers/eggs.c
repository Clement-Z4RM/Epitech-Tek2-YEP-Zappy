/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** eggs.c
*/

#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "eggs.h"
#include "../clients_manager.h"
#include "map/map.h"
#include <stdio.h>
#include "logs/logs.h"
#include "commands/gui/gui_commands.h"

void send_default_eggs(team_node_t *team, client_t *client)
{
    team_egg_t *egg_current = NULL;
    coords_t coords = {0, 0};

    SLIST_FOREACH(egg_current, &team->eggs, next) {
        coords.x = egg_current->egg->x;
        coords.y = egg_current->egg->y;
        enw_to_target(egg_current->egg->id, 0, client, &coords);
    }
}

/**
 * @brief Spawn egg on the map and assign it to a team at a given position
 *
 * @param map The map where to spawn the egg
 * @param team The team to assign the egg to
 * @param x The column where to spawn the egg
 * @param y The row where to spawn the egg
 *
 * @return true if the operation was successful,
 * false otherwise (allocation error)
 */
bool spawn_egg(map_t *map, team_node_t **team, u_int64_t x, u_int64_t y)
{
    egg_t *new_egg = malloc(sizeof(egg_t));
    team_egg_t *new_team_egg = malloc(sizeof(team_egg_t));

    if (!new_egg || !new_team_egg) {
        free(new_egg);
        free(new_team_egg);
        return false;
    }
    new_egg->id = map->egg_id;
    ++map->egg_id;
    new_egg->x = x;
    new_egg->y = y;
    SLIST_INSERT_HEAD(&map->cells[y][x].eggs, new_egg, next);
    new_team_egg->egg = new_egg;
    SLIST_INSERT_HEAD(&(*team)->eggs, new_team_egg, next);
    *team = SLIST_NEXT(*team, next);
    return true;
}

/**
 * @brief Spawn extra eggs on the map.
 * The used algorithm may not spawn al the eggs,
 * so we randomly spawn extra eggs.
 *
 * @param map The map where to spawn the eggs.
 * @param team The current team to assign the egg to.
 * @param teams The list of teams.
 * @param spawned The number of eggs already spawned.
 *
 * @return true if the operation was successful,
 * false otherwise (allocation error).
 */
static bool spawn_extra_eggs(
    map_t *map,
    team_node_t *team,
    team_list_t *teams,
    u_int64_t spawned
)
{
    for (u_int64_t i = 0; i < spawned; ++i) {
        if (!spawn_egg(map, &team, random() % map->x, random() % map->y))
            return false;
        if (!team)
            team = SLIST_FIRST(teams);
    }
    return true;
}

static bool spawn_eggs(
    map_t *map,
    team_node_t **team,
    team_list_t *teams,
    eggs_stats_t *eggs
)
{
    double x = eggs->spacing / 2;

    while (x < (double)map->x && eggs->spawned < eggs->total) {
        if (!spawn_egg(map, team, floor(x), floor(eggs->y)))
            return false;
        if (!*team)
            *team = SLIST_FIRST(teams);
        ++eggs->spawned;
        x += eggs->spacing;
    }
    return true;
}

/**
 * @brief Initialize all eggs on the map and assign them to teams
 * spreading them evently
 *
 * @param manager The clients manager
 * @param options The server options
 * @param map The map of the server
 *
 * @return true if the operation was successful,
 * false otherwise (allocation error)
 */
bool client_manager_init_eggs(
    clients_manager_t *manager,
    options_t *options,
    map_t *map
)
{
    eggs_stats_t eggs = {options->team_count * options->clients, 0, 0, 0};
    team_node_t *team;

    eggs.spacing = sqrt((double)(map->x * map->y) / (double)eggs.total);
    eggs.y = eggs.spacing / 2;
    SLIST_FOREACH(team, &manager->team_list, next)
        team->nb_eggs = options->clients;
    team = SLIST_FIRST(&manager->team_list);
    while (eggs.y < (double)map->y && eggs.spawned < eggs.total) {
        if (!spawn_eggs(map, &team, &manager->team_list, &eggs))
            return false;
        eggs.y += eggs.spacing;
    }
    spawn_extra_eggs(
        map,
        team,
        &manager->team_list,
        eggs.total - eggs.spawned
    );
    return true;
}
