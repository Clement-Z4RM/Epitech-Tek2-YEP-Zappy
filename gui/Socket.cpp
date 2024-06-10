/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** Socket.cpp
*/

#include "Socket.hpp"

int Socket::create(int domain, int type, int protocol) {
    int fd = socket(domain, type, protocol);
    if (fd == -1)
        throw std::runtime_error("Socket error");
    return fd;
}

int Socket::network(uint16_t port) {
    int network = htons(port);
    return network;
}

in_addr_t Socket::adress(std::string &str) {
    int validity = inet_aton(str.c_str(), NULL);
    if (validity == 0)
        throw std::runtime_error("Invalid IP adress");
    in_addr_t adress = inet_addr(str.c_str());
    return adress;
}

int Socket::close_socket(int fd) {
    return close(fd);
}

int Socket::select_socket(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout) {
    int open = select(nfds, readfds, writefds, exceptfds, timeout);
    if (open == -1)
        throw std::runtime_error("Select error");
    return open;
}

int Socket::send_socket(int fd, const void *buf, size_t len, int flags) {
    return send(fd, buf, len, flags);
}
