/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** cancel.c
*/

#include "incantation.h"

void cancel_incantation(incantation_t *incantation)
{
    incantation_player_t *player;

    SLIST_FOREACH(player, &incantation->players, next) {
        player->player->client->busy = false;
        add_request_to_all_players(incantation, "ko\n");
    }
    incantation->destroy(incantation);
}
