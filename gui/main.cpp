/*
** EPITECH PROJECT, 2024
** Epitech-Tek2-YEP-Zappy
** File description:
** main.cpp
*/

#include "GUI/Gui.hpp"

int main(int ac, char **av)
{
    if (ac == 2 && std::string(av[1]) == "-help") {
        std::cout << "USAGE: ./zappy_gui -p port -h machine" << std::endl;
        return 0;
    }
    if (ac != 5 || std::strcmp(av[1], "-p") || std::strtoll(av[2], NULL, 10) < 0 || std::strcmp(av[3], "-h"))
        return 84;
    std::string ip = av[4];
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
