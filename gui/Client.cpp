/*
** EPITECH PROJECT, 2024
** Epitech_Tek2_YEP_Zappy
** File description:
** Client.cpp
*/

#include "Client.hpp"

namespace gui {
    Client::Client(std::string &ip, int port)
    {
        int sfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sfd == -1)
            perror("Socket error");
        struct sockaddr_in client;
        client.sin_family = AF_INET;
        client.sin_port = htons(port);
        client.sin_addr.s_addr = inet_addr(ip.c_str());
        if (connect(sfd, (struct sockaddr *)&client, (socklen_t)sizeof(client)) == -1)
        {
            perror("Don't connect");
            exit(84);
        }
        _sfd = sfd;
        _param._port = port;
        _param._machine = ip;
    }

    Client::~Client()
    {
        close(_sfd);
    }

    void Client::readSocket()
    {
        fd_set rfds;
        struct timeval tv;
        int retval;
        char buff[8192];
        memset(buff, 0, 8192);

        std::string str;

        if (!isReady())
            return;

        ssize_t bytes_received;
        bytes_received = read(_sfd, buff, 8192);
        if (bytes_received == -1)
            perror("No buffer");
        str = buff;
        parseMsg(str);
    }

    bool Client::isReady()
    {
        fd_set readfds;
        struct timeval timeout;
        int ready = 0;

        FD_ZERO(&readfds);
        FD_SET(_sfd, &readfds);
        timeout.tv_sec = 0.1;
        timeout.tv_usec = 0;
        ready = select(_sfd + 1, &readfds, NULL, NULL, &timeout);
        if (ready == -1) {
            printf("select");
            return false;
        }
        return true;
    }

    void Client::sendMsg(std::string &msg)
    {
        send(_sfd, msg.c_str(), msg.size(), 0);
    }

    void Client::parseMsg(std::string &msg)
    {
        if (msg == "WELCOME\n" && !isConnected) {
            isConnected = true;
            return;
        }
        if (_param._width < 0 && _param._height < 0)
            getMapSize(msg);
        if (_param._freq < 0)
            getFrequency(msg);
        getCases(msg);
    }

    void Client::getMapSize(std::string &msg)
    {
        int size = msg.find("msz") + 4;
        if (size < 4) {
            return;
        }
        std::string x = msg.substr(size, msg.find(" ", size) - size);
        size = msg.find(" ", size) + 1;
        std::string y = msg.substr(size, msg.find("\n", size) - size);
        _param._width = std::stoi(x);
        _param._height = std::stoi(y);
    }

    void Client::getFrequency(std::string &msg)
    {
        int freq = msg.find("sgt") + 4;
        if (freq <= 4)
            return;
        std::string f = msg.substr(freq, msg.find("\n", freq) - freq);
        _param._freq = std::stoi(f);
    }

    void Client::getCases(std::string &msg)
    {
        for (int i = 0; i < msg.size(); i++) {
            if (msg[i] == '\n') {
                if (_incompleteCase) {
                    _map.back().append(msg.substr(0, i));
                    _incompleteCase = false;
                    msg = msg.substr(i + 1);
                    i = 0;
                    continue;
                }
                _map.push_back(msg.substr(0, i));
                msg = msg.substr(i + 1);
                i = 0;
            }
        }
        if (!msg.empty()) {
            _map.push_back(msg);
            _incompleteCase = true;
        }
        if (_map.empty())
            return;
        for (auto &line : _map) {
            std::stringstream s(line);
            std::string btc;
            std::string x;
            std::string y;
            s >> btc;
            s >> x;
            s >> y;
            if (btc != "bct" || std::atoi(x.c_str()) != _param._width - 1 ||
                std::atoi(y.c_str()) != _param._height - 1) {
            } else {
                this->isMapFinished = true;
                this->isParamGet = false;
            }
        }
    }

    void Client::parseMap()
    {
        std::deque<std::string> tmpMap;
        std::deque<std::string> otherParam;
        for (auto &i : _map) {
            if (i.find("bct") != std::string::npos)
                tmpMap.push_back(i);
            else
                otherParam.push_back(i);
        }
        for (auto &coo : tmpMap) { // TODO: check bct 17 6 with /032 /032
            std::stringstream s(coo);
            std::shared_ptr<Case> new_case = std::make_shared<Case>();
            new_case->createCase(s);
            _param._map.push_back(new_case);
        }
    }
} // gui