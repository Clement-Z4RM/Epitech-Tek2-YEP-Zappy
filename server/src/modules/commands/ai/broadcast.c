/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** broadcast.c
*/

#include <string.h>
#include <math.h>
#include "requests_manager/requests_manager.h"
#include "angle_direction.h"
#include "responses.h"

static int calc_cell_direction(int bpos, int o)
{
    int result = bpos + (2 * (o - 1));

    if (result > 8)
        result -= 8;
    return result;
}

static double calc_theta(map_t *map, double x_diff, double y_diff)
{
    double theta;

    if (x_diff > (double)map->width / 2)
        x_diff -= (double)map->width;
    else if (x_diff < (double)-map->width / 2)
        x_diff += (double)map->width;
    if (y_diff > (double)map->height / 2)
        y_diff -= (double)map->height;
    else if (y_diff < (double)-map->height / 2)
        y_diff += (double)map->height;
    theta = atan2(y_diff, x_diff);
    return theta;
}

static int get_direction_tile(
    player_t *emitter,
    player_t *receiver,
    map_t *map
)
{
    int o = emitter->direction;
    double x_diff = (double)receiver->x - (double)emitter->x;
    double y_diff = (double)receiver->y - (double)emitter->y;
    angle_direction_t directions[] = {
        {3 * M_PI / 8, 5 * M_PI / 8, calc_cell_direction(1, o)},
        {5 * M_PI / 8, 7 * M_PI / 8, calc_cell_direction(2, o)},
        {7 * M_PI / 8, 9 * M_PI / 8, calc_cell_direction(3, o)},
        {9 * M_PI / 8, 11 * M_PI / 8, calc_cell_direction(4, o)},
        {11 * M_PI / 8, 13 * M_PI / 8, calc_cell_direction(5, o)},
        {13 * M_PI / 8, 15 * M_PI / 8, calc_cell_direction(6, o)},
        {-M_PI / 8, M_PI / 8, calc_cell_direction(7, o)},
        {M_PI / 8, 3 * M_PI / 8, calc_cell_direction(8, o)},
    };
    double t = calc_theta(map, x_diff, y_diff);

    for (ulong i = 0; i < sizeof(directions) / sizeof(directions[0]); ++i)
        if (t >= directions[i].min_angle && t < directions[i].max_angle)
            return directions[i].direction;
    return 0;
}

static bool broadcast_null_value(char *arg, client_t *client)
{
    if (!arg) {
        client_add_request(client, strdup("ko\n"), TO_SEND);
        return true;
    }
    return false;
}

static void handle_current_client(ai_client_node_t *current_ai, ai_client_node_t
    *client, updater_t *updater, char *arg)
{
    char response[MAX_RESPONSE_SIZE];

    if (current_ai->player.id != client->player.id) {
        snprintf(response, MAX_RESPONSE_SIZE, "message %d,%s\n",
            get_direction_tile(&client->player, &current_ai->player,
                updater->map), arg
        );
        client_add_request(current_ai->client, strdup(response), TO_SEND);
    } else {
        client_add_request(current_ai->client, strdup("ok\n"), TO_SEND);
    }
}

static void broadcast_updater(
    ai_client_node_t *client,
    updater_t *updater,
    void *arg
)
{
    team_node_t *current_team;
    ai_client_node_t *current_ai;

    client->client->busy = false;
    if (broadcast_null_value(arg, client->client))
        return;
    SLIST_FOREACH(current_team,
        &updater->network->clients_manager->team_list,
        next) {
        SLIST_FOREACH(current_ai, &current_team->ai_clients, next) {
            handle_current_client(current_ai, client, updater, arg);
        }
    }
    pbc(client->player.id, (char *)arg, updater->network->clients_manager);
    free(arg);
}

/**
 * @brief Broadcast command.
 * Send a message to all players, but without the sender, only the source tile.
 *
 * This command takes 7 ticks to execute.
 *
 * @param data The structure containing all needed informations.
 */
// TODO: message parsing (cf. to-do list)
void broadcast(ai_handler_data_t *data)
{
    command_updater_data_t updater_data = {
        data->updater->elapsed,
        7,
        data->client,
        data->client->player.id,
        NULL
    };

    if (data->args[1] == NULL)
        return;
    updater_data.arg = (void *)strdup(data->args[1]);
    data->client->client->busy = true;
    updater_add_command(data->updater, &updater_data, broadcast_updater);
}
