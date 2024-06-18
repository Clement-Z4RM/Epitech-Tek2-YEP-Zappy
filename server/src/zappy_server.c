/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** zappy_server.c
*/

#include <time.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include "options/options.h"
#include "network/network.h"
#include "requests_manager/requests_manager.h"
#include "map/map.h"
#include "logs/logs.h"
#include "macros.h"
#include "utilities.h"
#include "zappy_server.h"

static bool loop(bool stop)
{
    static bool _loop = true;

    if (stop)
        _loop = false;
    return _loop;
}

static void sig_handler(UNUSED int signum)
{
    loop(true);
}

static int destroy(network_t *network, map_t *map, int to_return)
{
    if (network)
        network->destroy(network);
    if (map)
        map->destroy(map);
    return to_return;
}

static int server_loop(options_t *options)
{
    network_t *network = network_constructor("127.0.0.1", options->port);
    map_t *map = create_map(options->world.x, options->world.y);

    if (!network || !map)
        return destroy(network, map, 84);
    catch_signal(SIGINT, sig_handler);
    catch_signal(SIGTERM, sig_handler);
    while (loop(false)) {
        if (!network_set_and_select_fds(network))
            return destroy(network, map, 84);
        if (!network_receive_requests(network))
            return destroy(network, map, 84);
        if (!network_send_requests(network))
            return destroy(network, map, 84);
        requests_manager_handle_requests(network->clients_manager);
    }
    LOG_SUCCESS("Server stopped\n");
    return destroy(network, map, 0);
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
    srandom(time(NULL));
    if (server_loop(options) == 84) {
        options->destroy(options);
        return 84;
    }
    options->destroy(options);
    return 0;
}
