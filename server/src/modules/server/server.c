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
#include "updater/updater.h"
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
 * @param updater The updater structure to destroy.
 */
static void destroy(
    network_t *network,
    map_t *map,
    updater_t *updater
)
{
    if (network)
        network->destroy(network);
    if (map)
        map->destroy(map);
    if (updater)
        updater->destroy(updater);
}

/**
 * @brief The Zappy server loop.
 *
 * @param network The network structure.
 * @param map The map structure.
 * @param updater The updater structure.
 *
 * @return true if the program ran successfully, false otherwise.
 */
static bool server_loop(network_t *network, map_t *map, updater_t *updater)
{
    time_t start = 0;

    for (time_t elapsed = 0; loop(false); elapsed = mstime(NULL) - start) {
        if (0 != start)
            updater->update(updater, elapsed);
        switch (network_set_and_select_fds(network)) {
            case ERROR:
                return false;
            case EINTR:
                return true;
        }
        if (!network_receive_requests(network))
            return false;
        if (!network_send_requests(network))
            return false;
        requests_manager_handle_requests(network->clients_manager, map);
    }
    return true;
}

/**
 * @brief The main function of the Zappy server.
 * It initializes all the necessary structures and starts the server loop.
 *
 * @param options The options of the server.
 *
 * @return true if the program ran successfully, false otherwise.
 */
bool server(options_t *options)
{
    network_t *network = network_constructor("127.0.0.1", options);
    map_t *map = create_map(options->world.x, options->world.y);
    updater_t *updater = create_updater(network, map);
    bool to_return;

    if (!network || !map || !updater) {
        destroy(network, map, updater);
        LOG_FAILURE("Server stopped\n");
        return false;
    }
    catch_signal(SIGINT, sig_handler);
    catch_signal(SIGTERM, sig_handler);
    to_return = server_loop(network, map, updater);
    destroy(network, map, updater);
    if (to_return)
        LOG_SUCCESS("Server stopped\n");
    else
        LOG_FAILURE("Server stopped\n");
    return to_return;
}
