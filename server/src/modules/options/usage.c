/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** usage.c
*/

#include <stdio.h>
#include "options/options.h"

/**
 * @brief Display the usage of the program depending on the options
 * If the usage option (-h) is set, it will display the usage
 * and destroy the options structure
 *
 * @param options The options structure to check
 *
 * @return true if the usage option is set, false otherwise
 */
bool usage(options_t *options)
{
    if (!options->usage)
        return false;
    printf("USAGE: ./zappy_server -p port -x width -y height"
        " -n name1 name2 ... -c clientsNb -f freq\n");
    options->destroy(options);
    return true;
}
