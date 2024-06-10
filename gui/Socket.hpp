/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** Socket.hpp
*/

#pragma once
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/select.h>
#include <iostream>

class Socket {
public:
    static int create(int domain, int type, int protocol);

    static int network(uint16_t port);

    static in_addr_t adress(std::string &str);

    static int connection(int fd, const sockaddr *addr, socklen_t len) {
        int connection = connect(fd, addr, len);
        if (connection == -1)
            throw std::runtime_error("Connection error");
        return connection;
    }

    static int close_socket(int fd);

    static ssize_t read_socket(int fd, char *buff, size_t len) {
        return read(fd, buff, len);
    }

    static int select_socket(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);

    static int send_socket(int fd, const void *buf, size_t len, int flags);
};
