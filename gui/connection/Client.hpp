/*
** EPITECH PROJECT, 2024
** Epitech_Tek2_YEP_Zappy
** File description:
** Client.hpp
*/

#pragma once
#include <string>
#include <iostream>
#include <memory>
#include <cstring>
#include <deque>
#include <sstream>
#include "Socket.hpp"
#include "../Parameters.hpp"
#include "Sleep.hpp"
#include <SFML/Graphics.hpp>
namespace gui {
    class Client {
    public:
        Client(std::string &ip, int port);
        ~Client();

        void readSocket();
        bool isReady() const;
        void sendMsg(std::string &msg) const;

        void parseMsg(std::string &msg);

        void getMapSize(std::string &msg);
        void getFrequency(std::string &msg);
        void getCases(std::string &msg);

        void parseParameters();
        void parseMap(std::deque<std::string> &map);
        void parsePlayer(std::deque<std::string> &player);
        void parseShift(std::deque<std::string> &shift);
        void parseDeath(std::deque<std::string> &death);
        void parseTeam(std::deque<std::string> &teams);
        void parseInventory(std::deque<std::string> &inventory);

        void refreshMap();

        bool isConnected = false;
        bool isParamGet = true;
        bool isMapFinished = false;

        std::deque<std::string> &getMap() { return _map; }

        Parameters &getParam() { return _param; }

        void clearData();

        std::string tmp;
    private:
        int _sfd;
        Parameters _param;
        std::deque<std::string> _map;
        bool _incompleteCase = false;
        std::deque<std::shared_ptr<Case>> _saveMap;
    };

} // gui
