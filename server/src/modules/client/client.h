/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** client module
*/

#pragma once

/** @brief represent a client module **/
typedef struct client_s {
    int socket; ///< the socket of the client
    char *team_name; ///< the team name of the client
} client_t;

/**
* @brief create a new instance of the module client
* @param socket the socket of the client
* @return client_t the newly allocated instance
* **/
client_t *client_create(int socket);

/**
* @brief destroy a client instance
* @param client  the client to destroy
*/
void client_destroy(client_t *client);
