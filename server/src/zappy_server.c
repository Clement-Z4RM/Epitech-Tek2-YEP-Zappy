/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** zappy_server.c
*/

#include "utilities.h"

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
    options->destroy(options);
    return 0;
}
