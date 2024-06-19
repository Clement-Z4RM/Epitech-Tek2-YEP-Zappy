/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** catch_signal.c
*/

#include <signal.h>
#include <stdio.h>
#include "macros.h"

/**
 * @brief Catch the signum signal
 *
 * @param signum Signal number
 * @param handler Signal handler function
 */
void catch_signal(int signum, void (*handler)(int))
{
    struct sigaction sa;

    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = handler;
    if (sigaction(signum, &sa, NULL) == ERROR)
        perror("sigaction");
}
