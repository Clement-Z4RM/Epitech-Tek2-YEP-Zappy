/*
** EPITECH PROJECT, 2024
** Epitech-Tek2-YEP-Zappy
** File description:
** main.cpp
*/

#include "Client.hpp"

int main(int ac, char **av)
{
    if (ac != 3 || std::strtoll(av[2], NULL, 10) < 0 || std::strtoll(av[2], NULL, 10) > 65535)
        return 84;
    std::string ip = av[1];
    gui::Client graphic(ip, atoi(av[2]));
    graphic.readSocket();
    if (!graphic.isConnected)
        return 84;
    std::string id = "GRAPHIC\n";
    graphic.sendMsg(id);
//    while (graphic.isReady() && graphic.getParam)
    graphic.readSocket();
    graphic.readSocket();
    return 0;
}
