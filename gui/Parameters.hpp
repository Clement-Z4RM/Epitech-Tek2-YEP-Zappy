/*
** EPITECH PROJECT, 2024
** Epitech_Tek2_YEP_Zappy
** File description:
** Parameters.hpp
*/

#pragma once
#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include <deque>
#include "Player.hpp"
#include "src/egg.hpp"

class Case {
    public:
        Case() = default;
        ~Case() = default;

        bool isComplete() {
            if (_x == -1 || _y == -1 || _food == -1 || _linemate == -1 || _deraumere == -1 || _sibur == -1 || _mendiane == -1 || _phiras == -1 || _thystame == -1)
                return false;
            return true;
        }

        void createCase(std::stringstream &s) {
            std::string tmp;
            s >> tmp;
            s >> tmp;
            _x = std::stoi(tmp);
            s >> tmp;
            _y = std::stoi(tmp);
            s >> tmp;
            _food = std::stoi(tmp);
            s >> tmp;
            _linemate = std::stoi(tmp);
            s >> tmp;
            _deraumere = std::stoi(tmp);
            s >> tmp;
            _sibur = std::stoi(tmp);
            s >> tmp;
            _mendiane = std::stoi(tmp);
            s >> tmp;
            _phiras = std::stoi(tmp);
            s >> tmp;
            _thystame = std::stoi(tmp);
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

        std::deque<std::shared_ptr<Player>> getPlayerOnCase(std::shared_ptr<Case> c) {
            std::deque<std::shared_ptr<Player>> players;
            for (auto &player : _players) {
                if (player->getPosition()._x == c->_x && player->getPosition()._y == c->_y)
                    players.push_back(player);
            }
            return players;
        }

        int _width{-1};
        int _height{-1};
        int _port;
        std::string _machine;
        std::string _name {"Zappy"};
        int _clientsNb {-1};
        int _freq {-1};
        std::vector<std::string> _teams;
        std::deque<std::shared_ptr<Player>> _players;
        std::deque<std::shared_ptr<Case>> _map;
};
