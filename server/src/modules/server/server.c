/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** server.c
*/

#include <time.h>
#include <signal.h>
#include <errno.h>
#include "network/network.h"
#include "requests_manager/requests_manager.h"
#include "map/map.h"
#include "logs/logs.h"
#include "macros.h"
#include "utilities.h"

/**
 * @brief Store the loop state.
 *
 * @param stop If true, the loop will stop.
 *
 * @return The loop state.
 */
static bool loop(bool stop)
{
    static bool _loop = true;

    if (stop)
        _loop = false;
    return _loop;
}

/**
 * @brief The signal handler for the server.
 */
static void sig_handler(UNUSED int signum)
{
    loop(true);
}

/**
 * @brief Destroy the network and the map structures.
 *
 * @param network The network structure to destroy.
 * @param map The map structure to destroy.
 * @param to_return The value to return.
 *
 * @return The value to return (`to_return`).
 */
static int destroy(network_t *network, map_t *map, int to_return)
{
    if (network)
        network->destroy(network);
    if (map)
        map->destroy(map);
    if (0 == to_return)
        LOG_SUCCESS("Server stopped\n");
    else
        LOG_FAILURE("Server stopped\n");
    return to_return;
}

/**
 * @brief The main function of the Zappy server containing the server loop.
 *
 * @param options The options of the server.
 *
 * @return 0 if the program ran successfully, 84 otherwise.
 */
int server_loop(options_t *options)
{
    network_t *network = network_constructor("127.0.0.1", options);
    map_t *map = create_map(options->world.x, options->world.y);
    time_t start = time(NULL);

    if (!network || !map)
        return destroy(network, map, 84);
    catch_signal(SIGINT, sig_handler);
    catch_signal(SIGTERM, sig_handler);
    for (UNUSED time_t elapsed = 0; loop(false); elapsed = start - time(NULL)) {
        switch (network_set_and_select_fds(network)) {
            case ERROR:
                return destroy(network, map, 84);
            case EINTR:
                return destroy(network, map, 0);
        }
        if (!network_receive_requests(network))
            return destroy(network, map, 84);
        if (!network_send_requests(network))
            return destroy(network, map, 84);
        requests_manager_handle_requests(network->clients_manager);
    }
    return destroy(network, map, 0);
}
