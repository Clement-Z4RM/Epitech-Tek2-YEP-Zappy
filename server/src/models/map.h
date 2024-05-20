/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** map.h
*/

#ifndef ZAPPY_SERVER_MAP_H_
#define ZAPPY_SERVER_MAP_H_

#include <sys/types.h>

typedef struct cell_s {
    struct cell_s *up;
    struct cell_s *left;
    uint x;
    uint y;
    struct cell_s *right;
    struct cell_s *down;
} cell_t;

#endif /* !ZAPPY_SERVER_MAP_H_ */
