/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** zappy_server.c
*/

#include "options/options.h"
#include "modules/network/network.h"
#include "signal.h"
#include "stdio.h"
#include "../include/zappy_server.h"

static void sig_handler(int signum)
{
    (void)signum;
    server_state = SERVER_STOPPED;
}

static int server_loop(options_t *options)
{
    network_t *network = network_constructor("127.0.0.1", options->port);

    signal(SIGINT, sig_handler);
    signal(SIGTERM, sig_handler);
    while (server_state == SERVER_RUNNING) {
        if (!network_set_and_select_fds(network)) {
            network_destructor(network);
            return 84;
        }
        if (FD_ISSET(network->endpoint->socket, &network->read_fds) &&
            !network_accept_connexion(network)
            ) {
            network_destructor(network);
            return 84;
        }
    }
    return 0;
}

/**
 * @brief The main function of the Zappy server
 *
 * @param argc Program argument count
 * @param argv Program argument vector
 *
 * @return 0 if the program ran successfully, 84 otherwise
 */
int zappy_server(int argc, char *argv[])
{
    options_t *options = parse_options(argc, argv);

    if (!options)
        return 84;
    if (usage(options))
        return 0;
    if (server_loop(options) == 84) {
        options->destroy(options);
        return 84;
    }
    options->destroy(options);
    return 0;
}
