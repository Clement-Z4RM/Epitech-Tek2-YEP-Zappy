/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** command_updater.c
*/

#include <stdio.h>
#include <string.h>
#include "updater.h"

/**
 * @brief Add a command to the command updaters queue of the updater.
 *
 * @param updater The updater where the command will be added.
 * @param data The data needed to execute the command.
 * @param command_updater_func The function that will be executed.
 *
 * @return The command updater if it was successfully created,
 * NULL otherwise (allocation error).
 */
command_updater_t *updater_add_command(
    updater_t *updater,
    command_updater_data_t *data,
    command_updater_func_t command_updater_func
)
{
    command_updater_t *command_updater = malloc(sizeof(command_updater_t));

    if (!command_updater) {
        perror("malloc");
        client_add_request(data->client->client, strdup("ko\n"), TO_SEND);
        return NULL;
    }
    memcpy(&command_updater->data, data, sizeof(command_updater_data_t));
    command_updater->updater = command_updater_func;
    CIRCLEQ_INSERT_TAIL(&updater->command_updaters, command_updater, next);
    return command_updater;
}

static bool command_should_be_executed(
    command_updater_data_t *data,
    updater_t *updater
)
{
    time_t execute_at = (time_t)(
        data->executed_at +
        ((data->time * 1000) / updater->network->options->freq)
    );

    if (execute_at <= updater->elapsed)
        return true;
    return false;
}

static bool disconnected_client(
    updater_t *updater,
    command_updater_t *_updater
)
{
    if (!clients_manager_get_ai_by_id(
        updater->network->clients_manager,
        _updater->data.id
    )) {
        CIRCLEQ_REMOVE(&updater->command_updaters, _updater, next);
        free(_updater);
        return true;
    }
    return false;
}

/**
 * @brief Execute all the commands which should be executed (time elapsed)
 * of the command updaters queue.
 *
 * @param updater The updater where the commands are stored.
 */
void updater_execute_commands(updater_t *updater)
{
    command_updater_t *_updater = CIRCLEQ_FIRST(&updater->command_updaters);
    command_updater_t *tmp;

    for (; _updater && _updater != (void *)&updater->command_updaters;
        _updater = tmp) {
        tmp = CIRCLEQ_NEXT(_updater, next);
        if (disconnected_client(updater, _updater))
            continue;
        if (command_should_be_executed(&_updater->data, updater)) {
            _updater->updater(
                _updater->data.client,
                updater,
                _updater->data.arg
            );
            CIRCLEQ_REMOVE(&updater->command_updaters, _updater, next);
            free(_updater);
        }
    }
}
