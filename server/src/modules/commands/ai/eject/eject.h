/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** eject.h
*/

#ifndef ZAPPY_SERVER_EJECT_H_
    #define ZAPPY_SERVER_EJECT_H_

    #include "player/player.h"

static const player_direction_t EJECTION_DIRECTION[][3] = {
    {PD_UP, PD_UP, PD_DOWN},
    {PD_UP, PD_RIGHT, PD_RIGHT},
    {PD_UP, PD_DOWN, PD_UP},
    {PD_UP, PD_LEFT, PD_LEFT},
    {PD_RIGHT, PD_UP, PD_LEFT},
    {PD_RIGHT, PD_RIGHT, PD_DOWN},
    {PD_RIGHT, PD_DOWN, PD_RIGHT},
    {PD_RIGHT, PD_LEFT, PD_UP},
    {PD_DOWN, PD_UP, PD_UP},
    {PD_DOWN, PD_RIGHT, PD_LEFT},
    {PD_DOWN, PD_DOWN, PD_DOWN},
    {PD_DOWN, PD_LEFT, PD_RIGHT},
    {PD_LEFT, PD_UP, PD_RIGHT},
    {PD_LEFT, PD_RIGHT, PD_UP},
    {PD_LEFT, PD_DOWN, PD_LEFT},
    {PD_LEFT, PD_LEFT, PD_DOWN},
    {0, 0, 0}
};

#endif /* !ZAPPY_SERVER_EJECT_H_ */
