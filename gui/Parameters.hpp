/*
** EPITECH PROJECT, 2024
** Epitech_Tek2_YEP_Zappy
** File description:
** Parameters.hpp
*/

#pragma once
#include <string>
#include <vector>

class Egg {
    public:
        Egg() = default;
        ~Egg() = default;

        int _id;
        int _x;
        int _y;
        int _team;
        int _hatching;
};

class Case {
    public:
        Case() = default;
        ~Case() = default;

        bool isComplete() {
            if (_x == -1 || _y == -1 || _food == -1 || _linemate == -1 || _deraumere == -1 || _sibur == -1 || _mendiane == -1 || _phiras == -1 || _thystame == -1)
                return false;
            return true;
        }

        int _x {-1};
        int _y {-1};
        int _food {-1};
        int _linemate {-1};
        int _deraumere {-1};
        int _sibur {-1};
        int _mendiane {-1};
        int _phiras {-1};
        int _thystame {-1};
        std::vector<Egg> _eggs;
};

class Parameters {
    public:
        Parameters() = default;
        ~Parameters() = default;

        int _width{-1};
        int _height{-1};
        int _port;
        std::string _machine;
        std::string _name {"Zappy"};
        int _clientsNb {-1};
        int _freq {-1};
        std::vector<std::string> _teams;
        std::deque<Case> _map;
};
