/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** send_string.c
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

ssize_t send_string(int sockfd, const char *buf)
{
    return send(sockfd, buf, strlen(buf), 0);
}
