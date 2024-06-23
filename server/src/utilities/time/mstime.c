/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** mstime.c
*/

#include <sys/time.h>
#include <stddef.h>

/**
 * @brief Not affiliated with Microsoft.
 *
 * Returns the time as the number of milliseconds since the Epoch.
 * If tloc is non-NULL, the return value is also stored in the memory pointed
 * to by tloc.
 *
 * @param tloc The memory where the return value is stored if tloc is non-NULL.
 *
 * @return The time as the number of milliseconds since the Epoch.
 */
time_t mstime(time_t *tloc)
{
    struct timeval tv;
    time_t time;

    gettimeofday(&tv, NULL);
    time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    if (tloc)
        *tloc = time;
    return time;
}
