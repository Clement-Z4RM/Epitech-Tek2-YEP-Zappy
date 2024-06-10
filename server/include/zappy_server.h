/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** zappy_server.h
*/

#ifndef ZAPPY_SERVER_ZAPPY_SERVER_H_
    #define ZAPPY_SERVER_ZAPPY_SERVER_H_

typedef enum server_state_e {
    SERVER_RUNNING,
    SERVER_STOPPED
} server_state_t;

extern int zappy_server(int argc, char *argv[]);

static volatile server_state_t server_state = SERVER_RUNNING;

#endif /* !ZAPPY_SERVER_ZAPPY_SERVER_H_ */
