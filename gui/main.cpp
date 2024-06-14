/*
** EPITECH PROJECT, 2024
** Epitech-Tek2-YEP-Zappy
** File description:
** main.cpp
*/

#include "GUI/Gui.hpp"

int main(int ac, char **av)
{
    if (ac != 3 || std::strtoll(av[2], NULL, 10) < 0 || std::strtoll(av[2], NULL, 10) > 65535)
        return 84;
    std::string ip = av[1];
    std::string port = av[2];
    try {
        gui::GUI gui(ip, port);
        gui.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
