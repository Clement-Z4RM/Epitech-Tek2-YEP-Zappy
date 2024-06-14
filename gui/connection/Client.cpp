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
        int sfd = Socket::create(AF_INET, SOCK_STREAM, 0);
        if (sfd == -1)
            std::cerr << "Socket error" << std::endl;
        struct sockaddr_in client{};
        client.sin_family = AF_INET;
        client.sin_port = Socket::network(port);
        client.sin_addr.s_addr = Socket::adress(ip);
        if (Socket::connection(sfd, (struct sockaddr *)&client, (socklen_t)sizeof(client)) == -1)
            throw std::runtime_error("Connection error");
        _sfd = sfd;
        _param._port = port;
        _param._machine = ip;
    }

    Client::~Client()
    {
        Socket::close_socket(_sfd);
    }

    void Client::readSocket()
    {
        char buff[4096];

        if (!isReady())
            return;
        std::memset(buff, 0, 4096);
        ssize_t bytes_received;
        bytes_received = Socket::read_socket(_sfd, buff, 4095);
        if (bytes_received == -1)
            std::cerr << "No buffer" << std::endl;
        tmp = buff;
    }

    bool Client::isReady() const
    {
        fd_set readfds;
        struct timeval timeout{};
        int ready;

        FD_ZERO(&readfds);
        FD_SET(_sfd, &readfds);
        timeout.tv_sec = static_cast<time_t>(0.1);
        timeout.tv_usec = 0;
        ready = Socket::select_socket(_sfd + 1, &readfds, nullptr, nullptr, &timeout);
        if (ready == -1) {
            std::cout << "select" << std::endl;
            return false;
        }
        return true;
    }

    void Client::sendMsg(std::string &msg) const
    {
        Socket::send_socket(_sfd, msg.c_str(), msg.size(), 0);
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
        std::string::size_type size = msg.find("msz") + 4;
        if (size < 4) {
            return;
        }
        std::string x = msg.substr(size, msg.find(' ', size) - size);
        size = msg.find(' ', size) + 1;
        std::string y = msg.substr(size, msg.find('\n', size) - size);
        _param._width = std::stoi(x);
        _param._height = std::stoi(y);
    }

    void Client::getFrequency(std::string &msg)
    {
        std::string::size_type freq = msg.find("sgt") + 4;
        if (freq <= 4)
            return;
        std::string f = msg.substr(freq, msg.find('\n', freq) - freq);
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
            if (btc != "bct" || std::strtol(x.c_str(), nullptr, 10) != _param._width - 1 ||
            std::strtol(y.c_str(), nullptr, 10) != _param._height - 1) {
            } else {
                this->isMapFinished = true;
                this->isParamGet = false;
            }
        }
    }

    void Client::parseParameters()
    {
        std::deque<std::string> tmpMap;
        std::deque<std::string> otherParam;
        std::deque<std::string> players;
        std::deque<std::string> inventory;

        _param._map.clear();
        for (auto &i : _map) {
            if (i.find("bct") != std::string::npos)
                tmpMap.push_back(i);
            else if (i.find("pnw") != std::string::npos)
                players.push_back(i);
            else if (i.find("pin") != std::string::npos)
                inventory.push_back(i);
            else if (_param._eggs.checkMsg(i))
                continue;
            else
                otherParam.push_back(i);
        }
        for (auto &coo : tmpMap) {
            std::stringstream s(coo);
            std::shared_ptr<Case> new_case = std::make_shared<Case>();
            new_case->createCase(s);
            _param._map.push_back(new_case);
        }
        for (auto &player : players) {
            std::stringstream s(player);
            std::shared_ptr<Player> new_player = std::make_shared<Player>(s);
            _param._players.push_back(new_player);
        }
        for (auto &inv : inventory) {
            std::stringstream s(inv);
            std::string tmpData;
            s >> tmpData;
            s >> tmpData;
            int identifier = std::stoi(tmpData);
            s >> tmpData;
            int x = std::stoi(tmpData);
            s >> tmpData;
            int y = std::stoi(tmpData);
            for (auto &player : _param._players) {
                if (player->getId() == identifier && player->getPosition()._x == x && player->getPosition()._y == y) {
                    player->setInventory(s);
                    break;
                }
            }
        }
        for (auto &param : otherParam) {
            std::cout << param << std::endl;
        }
    }

    void Client::clearData()
    {
        std::string output;

        for (size_t i = 0; i < tmp.length(); ++i) {
            if (std::isprint(tmp[i]) || tmp[i] == '\n' && tmp[i] != '@') {
                output += tmp[i];
            } else if (!std::isprint(tmp[i])) {
                while (i < tmp.length() && !std::isprint(tmp[i])) {
                    ++i;
                }
                --i;
            }
        }
        tmp = output;
    }

    void Client::refreshMap()
    {
        Sleep::sleepInMicroSecond(_param._freq);
        this->isMapFinished = false;
        _map.clear();
        while (!this->isMapFinished) {
            this->readSocket();
            this->clearData();
            this->getCases(tmp);
        }
        this->parseParameters();
    }
} // gui