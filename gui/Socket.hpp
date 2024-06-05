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

class Socket {
public:
    static int create(int domain, int type, int protocol) {
        return socket(domain, type, protocol);
    };

    static int network(uint16_t port) {
        return htons(port);
    }

    static in_addr_t adress(std::string &str) {
        return inet_addr(str.c_str());
    }

    static int connection(int fd, const sockaddr *addr, socklen_t len) {
        return connect(fd, addr, len);
    }

    static int close_socket(int fd) {
        return close(fd);
    }

    static int read_socket(int fd, char *buff, size_t len) {
        return read(fd, buff, len);
    }

    static int select_socket(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout) {
        return select(nfds, readfds, writefds, exceptfds, timeout);
    }

    static int send_socket(int fd, const void *buf, size_t len, int flags) {
        return send(fd, buf, len, flags);
    }
};
