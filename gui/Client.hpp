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
#include "Parameters.hpp"

namespace gui {
    class Client {
    public:
        Client(std::string &ip, int port);
        ~Client();

        void readSocket();
        bool isReady();
        void sendMsg(std::string &msg);

        void parseMsg(std::string &msg);

        void getMapSize(std::string &msg);
        void getFrequency(std::string &msg);
        void getCases(std::string &msg);

        void parseMap();

        bool isConnected = false;
        bool isParamGet = true;
        bool isMapFinished = false;

        std::deque<std::string> &getMap() { return _map; }

        Parameters &getParam() { return _param; }

    private:
        int _sfd;
        Parameters _param;
        std::deque<std::string> _map;
        bool _incompleteCase = false;
    };

} // gui
