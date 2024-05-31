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
#include <iterator>
#include <regex>
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

        bool iter(std::sregex_token_iterator &it, std::sregex_token_iterator &end);

        void getMapSize(std::string &msg);
        void getFrequency(std::string &msg);
        void getCases(std::string &msg);
        void createCase(std::sregex_token_iterator &it, std::sregex_token_iterator &end);
        void completeCase(std::sregex_token_iterator &it, std::sregex_token_iterator &end);

        bool isConnected = false;
        bool getParam = true;

    private:
        int _sfd;
        Parameters _param;
        std::deque<std::string> _map;
    };

} // gui
