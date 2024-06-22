/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** angle_direction struct
*/

#pragma once
#include "sys/types.h"
typedef struct angle_direction_s {
    double min_angle;
    double max_angle;
    u_int8_t direction;
} angle_direction_t;
