/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** updater.c
*/

#include <stdio.h>
#include "updater.h"

/**
 * @brief Get the amount of life to remove from each player,
 * depending on the frequency and the time elapsed since the previous update.
 *
 * @param updater The updater structure,
 * containing the frequency and the time of the previous update.
 * @param elapsed The elapsed time since the server startup.
 *
 * @return The amount of life to remove.
 */
static double get_life_to_remove(updater_t *updater, time_t elapsed)
{
    return (double)(
        updater->network->options->freq * (elapsed - updater->previous_time)
    ) / 1000;
}

/**
 * @brief Update the map (resources) and the client (actions)
 * depending on the elapsed time and the frequency.
 *
 * @param updater The updater structure,
 * containing all the necessary data for the update.
 * @param elapsed The elapsed time since the server startup.
 */
static void update(updater_t *updater, time_t elapsed)
{
    double life_to_remove = get_life_to_remove(updater, elapsed);
    ai_client_node_t *client;

    if (elapsed >= updater->next_generation) {
        updater->map->resources.generate(updater->map);
        updater->next_generation = elapsed + updater->generation_interval;
    }
    SLIST_FOREACH(client, &updater->network->clients_manager->ai_clients_list, next) {
        client->player.life_span -= life_to_remove;
        if (client->player.life_span <= 0) {
            // TODO: death
        }
    }
    updater->previous_time = elapsed;
}

/**
 * @brief Updater structure destructor
 *
 * @param updater The updater to destroy
 */
static void updater_destructor(updater_t *updater)
{
    if (!updater)
        return;
    free(updater);
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
    updater_t *updater = malloc(sizeof(updater_t));

    if (!updater)
        return NULL;
    updater->previous_time = 0;
    updater->generation_interval = (time_t)(20000 / network->options->freq);
    if (0 == updater->generation_interval)
        updater->generation_interval = 1;
    updater->next_generation = updater->generation_interval;
    printf("Generation interval: %ld\n", updater->generation_interval);
    updater->network = network;
    updater->map = map;
    updater->update = update;
    updater->destroy = updater_destructor;
    return updater;
}
