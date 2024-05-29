/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** str_to_num.c
*/

#include <stdbool.h>
#include <stdlib.h>

/**
 * @brief Convert a string to a number.
 *
 * @param str The string to convert to a number
 * @param min The minimum value the number can be.
 * If the number is less than this, error will be set to true.
 * Set to LONG_MIN if you don't want to have a minimum.
 * @param max The maximum value the number can be.
 * If the number is greater than this, error will be set to true.
 * Set to LONG_MAX if you don't want to have a maximum.
 * @param error A pointer to a boolean
 * which will be set to true if an error occurred.
 * Errors can be: the string is not a (valid) number,
 * the number is less than min or greater than max.
 * If error is NULL, no check will be done
 * and the return value will be the number returned by strtol.
 *
 * @return The number as a long (undefined if there is an error)
 */
long str_to_num(const char *str, long min, long max, bool *error)
{
    char *end;
    long num = strtol(str, &end, 10);

    if (error && (str == end || *end || num < min || num > max))
        *error = true;
    return num;
}
