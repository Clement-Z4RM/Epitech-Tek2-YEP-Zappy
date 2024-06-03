/*
** EPITECH PROJECT, 2024
** Epitech_Tek2_YEP_Zappy
** File description:
** Client.hpp
*/

#pragma once
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/select.h>
#include <iostream>
#include <memory>
#include <cstring>
#include <deque>
#include <sstream>
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

        bool isConnected = false;
        bool getParam = true;
        bool isMapFinished = false;

        std::deque<std::string> &getMap() { return _map; }

    private:
        int _sfd;
        Parameters _param;
        std::deque<std::string> _map;
        bool _incompleteCase = false;
    };

} // gui
