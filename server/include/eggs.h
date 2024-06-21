/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** eggs.h
*/

#ifndef ZAPPY_SERVER_EGGS_H_
    #define ZAPPY_SERVER_EGGS_H_

    #include <sys/types.h>

typedef struct eggs_stats_s {
    u_int64_t total;
    u_int64_t spawned;
    double spacing;
    double y;
} eggs_stats_t;

#endif /* !ZAPPY_SERVER_EGGS_H_ */
