/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** str_to_port.c
*/

#include <limits.h>
#include "macros.h"
#include "utilities.h"

/**
 * @brief Parse a string to a port in unsigned short range (0-65535)
 *
 * @param str The port string to convert
 *
 * @return The port in unsigned short range, or -1 if the port is invalid
 *
 * @note The returned value can be cast to an unsigned short if port is valid
 */
int str_to_port(const char *str)
{
    bool error = false;
    long port = str_to_num(str, 1, USHRT_MAX, &error);

    if (error)
        return ERROR;
    return (int)port;
}
