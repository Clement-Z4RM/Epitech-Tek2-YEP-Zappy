/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** updater.c
*/

#include <stdio.h>
#include "utilities.h"
#include "updater.h"
#include "commands/gui/gui_commands.h"

/**
 * @brief Get the amount of life to remove from each player,
 * depending on the frequency and the time elapsed since the previous update.
 *
 * @param updater The updater structure,
 * containing the frequency and the time of the previous update.
 *
 * @return The amount of life to remove.
 */
static double get_life_to_remove(updater_t *updater)
{
    return (double)(
        updater->network->options->freq *
        (updater->elapsed - updater->previous_time)
    ) / 1000;
}

static void player_dead(
    ai_client_node_t *client,
    team_node_t *team,
    map_t *map,
    clients_manager_t *clients_manager
)
{
    cell_t *cell = &map->cells[client->player.y][client->player.x];

    if (!send_string(client->client->socket, "dead\n"))
        perror("send");
    SLIST_REMOVE(&cell->players, client, ai_client_node_s, next);
    SLIST_REMOVE(&team->ai_clients, client, ai_client_node_s, next);
    clients_manager_remove(clients_manager, client->client);
}

static void update_team_clients_life(
    team_node_t *team,
    map_t *map,
    double life_to_remove,
    clients_manager_t *clients_manager
)
{
    ai_client_node_t *client;

    SLIST_FOREACH(client, &team->ai_clients, next) {
        client->player.life_span -= life_to_remove;
        if (client->player.life_span <= 0) {
            pdi(client->player.id, clients_manager);
            player_dead(client, team, map, clients_manager);
        }
    }
}

/**
 * @brief Update the map (resources) and the client (actions)
 * depending on the elapsed time and the frequency.
 *
 * @param updater The updater structure,
 * containing all the necessary data for the update.
 */
static void update(updater_t *updater)
{
    double life_to_remove = get_life_to_remove(updater);
    team_node_t *team;
    gui_client_node_t *gui_client;

    if (updater->elapsed >= updater->next_generation) {
        updater->map->resources.generate(updater->map);
        updater->next_generation = updater->elapsed +
            updater->generation_interval;
        SLIST_FOREACH(gui_client,
            &updater->network->clients_manager->gui_clients_list, next) {
            mct_event(gui_client, updater);
        }
    }
    updater_execute_commands(updater);
    SLIST_FOREACH(team, &updater->network->clients_manager->team_list, next)
        update_team_clients_life(team, updater->map, life_to_remove,
            updater->network->clients_manager);
    updater->previous_time = updater->elapsed;
}

/**
 * @brief Updater structure destructor
 *
 * @param updater The updater to destroy
 */
static void updater_destructor(updater_t *updater)
{
    command_updater_t *tmp;

    if (!updater)
        return;
    while (!CIRCLEQ_EMPTY(&updater->command_updaters)) {
        tmp = CIRCLEQ_FIRST(&updater->command_updaters);
        CIRCLEQ_REMOVE(&updater->command_updaters, tmp, next);
        free(tmp);
    }
    free(updater);
}

void init_updater(updater_t *updater)
{
    updater->end_of_game = false;
    updater->update = update;
    updater->destroy = updater_destructor;
}

/**
 * @brief Initialize the updater structure.
 *
 * @param network The network structure.
 * @param map The map structure.
 *
 * @return The updater structure, or NULL if an allocation error occurred.
 */
updater_t *create_updater(network_t *network, map_t *map)
{
    updater_t *updater;

    if (!network || !map)
        return NULL;
    updater = malloc(sizeof(updater_t));
    if (!updater)
        return NULL;
    updater->start = 0;
    updater->elapsed = 0;
    updater->previous_time = 0;
    updater->generation_interval = (time_t)(20000 / network->options->freq);
    if (0 == updater->generation_interval)
        updater->generation_interval = 1;
    updater->next_generation = updater->generation_interval;
    CIRCLEQ_INIT(&updater->command_updaters);
    updater->network = network;
    updater->map = map;
    init_updater(updater);
    return updater;
}
