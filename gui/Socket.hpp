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
        int fd = socket(domain, type, protocol);
        if (fd == -1)
            throw std::runtime_error("Socket error");
        return fd;
    };

    static int network(uint16_t port) {
        int network = htons(port);
        return network;
    }

    static in_addr_t adress(std::string &str) {
        int validity = inet_aton(str.c_str(), NULL);
        if (validity == 0)
            throw std::runtime_error("Invalid IP adress");
        in_addr_t adress = inet_addr(str.c_str());
        return adress;
    }

    static int connection(int fd, const sockaddr *addr, socklen_t len) {
        int connection = connect(fd, addr, len);
        if (connection == -1)
            throw std::runtime_error("Connection error");
        return connection;
    }

    static int close_socket(int fd) {
        return close(fd);
    }

    static ssize_t read_socket(int fd, char *buff, size_t len) {
        return read(fd, buff, len);
    }

    static int select_socket(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout) {
        int open = select(nfds, readfds, writefds, exceptfds, timeout);
        if (open == -1)
            throw std::runtime_error("Select error");
        return open;
    }

    static int send_socket(int fd, const void *buf, size_t len, int flags) {
        return send(fd, buf, len, flags);
    }
};
