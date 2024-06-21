/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** connect_nbr.c
*/

#include <string.h>
#include "requests_manager/requests_manager.h"

/**
 * @brief Connect_nbr command.
 * Send the number of team unused slots.
 *
 * @param data The structure containing all needed informations.
 */
void connect_nbr(ai_handler_data_t *data)
{
    team_node_t *team = clients_manager_get_team_by_client(
        data->clients_manager,
        data->client
    );
    char *response;

    if (!team) {
        client_add_request(data->client->client, strdup("ok\n"), TO_SEND);
        return;
    }
    response = malloc(12);
    if (!response) {
        client_add_request(data->client->client, strdup("ok\n"), TO_SEND);
        return;
    }
    snprintf(response, 12, "%lu\n", team->nb_eggs);
    client_add_request(data->client->client, response, TO_SEND);
}
