/*
** EPITECH PROJECT, 2024
** Epitech-Tek2-YEP-Zappy
** File description:
** main.cpp
*/

#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/select.h>
#include <iostream>
#include <string>

int init_socket(char *ip, int port)
{
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1)
        perror("Socket error");
    struct sockaddr_in client;
    client.sin_family = AF_INET;
    client.sin_port = htons(port);
    client.sin_addr.s_addr = inet_addr(ip);
    if (connect(sfd, (struct sockaddr *)&client, (socklen_t)sizeof(client)) == -1)
    {
        perror("Don't connect");
        exit(84);
    }
    return sfd;
}

void read_socket(int sfd)
{
    fd_set rfds;
    struct timeval tv;
    int retval;
    std::string buff;

    FD_ZERO(&rfds);
    FD_SET(0, &rfds);
    tv.tv_sec = 5;
    tv.tv_usec = 0;

    ssize_t bytes_received;
    bytes_received = read(sfd, buff.c_str(), 4096);
    if (bytes_received == -1)
        perror("No buffer");
    std::cout << "Server: " << buff << std::endl;
}

int main(int ac, char **av)
{
    if (ac != 3)
        return 84;
    int sfd = init_socket(av[1], atoi(av[2]));
    read_socket(sfd);
    return 0;
}
