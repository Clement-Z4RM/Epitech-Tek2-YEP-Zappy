/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** broadcast.c
*/

#include "ai_commands.h"
#include "math.h"
#include "angle_direction.h"
#include "responses.h"

static int calc_cell_direction(int a)
{
    int b = -1.5 * a * a * a + 13.5 * a * a - 37 * a + 33;

    return b;
}

static int get_direction_tile(player_t *emitter, player_t *receiver, map_t *map)
{
    int o = receiver->direction;
    double x_diff = (double)receiver->x - (double)emitter->x;
    double y_diff = (double)receiver->y - (double)emitter->y;
    angle_direction_t directions[] = {
        {-M_PI / 8, M_PI / 8, calc_cell_direction(o)},
        {M_PI / 8, 3 * M_PI / 8, calc_cell_direction(o) + 1},
        {3 * M_PI / 8, 5 * M_PI / 8, calc_cell_direction(o) + 2},
        {5 * M_PI / 8, 7 * M_PI / 8, calc_cell_direction(o) + 3},
        {7 * M_PI / 8, 9 * M_PI / 8, calc_cell_direction(o) + 4},
        {9 * M_PI / 8, 11 * M_PI / 8, calc_cell_direction(o) + 5},
        {11 * M_PI / 8, 13 * M_PI / 8, calc_cell_direction(o) + 6},
        {13 * M_PI / 8, 15 * M_PI / 8, calc_cell_direction(o) + 7},
    };
    double theta = 0;

    if (x_diff > (double)map->width / 2)
        x_diff -= (double)map->width;
    else if (x_diff < (double)-map->width / 2)
        x_diff += (double)map->width;
    if (y_diff > (double)map->height / 2)
        y_diff -= (double)map->height;
    else if (y_diff < (double)-map->height / 2)
        y_diff += (double)map->height;
    theta = atan2(y_diff, x_diff);
    for (unsigned long i = 0; i < sizeof(directions) / sizeof(directions[0]);
        ++i)
        if (theta >= directions[i].min_angle && theta < directions[i].max_angle)
            return directions[i].direction;
    return 0;
}

void broadcast(ai_handler_data_t *data)
{
    char *msg = data->args[1];
    team_node_t *current_team;
    ai_client_node_t *current_ai;
    int direction = 0;
    char *response = malloc(MAX_RESPONSE_SIZE);

    if (msg == NULL)
        return;
    SLIST_FOREACH(current_team, &data->clients_manager->team_list, next) {
        SLIST_FOREACH(current_ai, &current_team->ai_clients, next) {
            direction = get_direction_tile(
                &data->client->player,
                &current_ai->player,
                data->map
            );
            snprintf(response, MAX_RESPONSE_SIZE, "message %d,%s\n",
                direction, msg);
            client_add_request(current_ai->client, response, TO_SEND);
        }
    }
}
