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
        char buff[4096];
        memset(buff, 0, 4096);

        std::string str;

        if (!isReady())
            return;

        ssize_t bytes_received;
        bytes_received = read(_sfd, buff, 4096);
        if (bytes_received == -1)
            perror("No buffer");
        str = buff;
//        std::cout << buff << std::endl;
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
        if (msg.find("bct"))
            getCases(msg);
    }

    void Client::getMapSize(std::string &msg)
    {
        int size = msg.find("msz") + 4;
        if (size <= 4)
            return;
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
        std::regex reg("\n", std::regex_constants::ECMAScript);
        std::sregex_token_iterator iter(msg.begin(), msg.end(), reg, -1);
        std::sregex_token_iterator end;
        for (; iter != end; ++iter) {
            std::regex reg2(" ", std::regex_constants::ECMAScript);
            std::sregex_token_iterator iter2(iter->first, iter->second, reg2, -1);
            std::sregex_token_iterator end2;
            if (iter2->str() == "bct" || (!_param._map.empty() && !_param._map.back().isComplete())) {
                if (!_param._map.empty() && !_param._map.back().isComplete()) {
                    std::cout << "Complete case" << std::endl;
                    completeCase(iter2, end2);
                    continue;
                }
                if (!this->iter(iter2, end2))
                    continue;
                createCase(iter2, end2);
            }
            std::cout << std::endl;
        }
    }

    bool Client::iter(std::sregex_token_iterator &it, std::sregex_token_iterator &end)
    {
        it++;
        if (it == end)
            return false;
        return true;
    }

    void Client::createCase(std::sregex_token_iterator &it, std::sregex_token_iterator &end)
    {
        std::cout << "Case: ";
        Case c;
        c._x = std::stoi(it->str());
        if (!iter(it, end)) {
            _param._map.push_back(c);
            return;
        }
        c._y = std::stoi(it->str());
        if (!iter(it, end)) {
            _param._map.push_back(c);
            return;
        }
        c._food = std::stoi(it->str());
        if (!iter(it, end)) {
            _param._map.push_back(c);
            return;
        }
        c._linemate = std::stoi(it->str());
        if (!iter(it, end)) {
            _param._map.push_back(c);
            return;
        }
        c._deraumere = std::stoi(it->str());
        if (!iter(it, end)) {
            _param._map.push_back(c);
            return;
        }
        c._sibur = std::stoi(it->str());
        if (!iter(it, end)) {
            _param._map.push_back(c);
            return;
        }
        c._mendiane = std::stoi(it->str());
        if (!iter(it, end))
            return;
        c._phiras = std::stoi(it->str());
        if (!iter(it, end)) {
            _param._map.push_back(c);
            return;
        }
        c._thystame = std::stoi(it->str());
        std::cout << c._x << " " << c._y << " " << c._food << " " << c._linemate << " " << c._deraumere << " " << c._sibur << " " << c._mendiane << " " << c._phiras << " " << c._thystame << std::endl;
        _param._map.push_back(c);
    }

    void Client::completeCase(std::sregex_token_iterator &it, std::sregex_token_iterator &end)
    {
        std::cout << "Case: ";
        Case c = _param._map.back();
        if (c._x == -1)
            c._x = std::stoi(it->str());
        if (!iter(it, end)) {
            // _param._map.pop_back();
            _param._map.push_back(c);
            return;
        }
        if (c._y == -1)
            c._y = std::stoi(it->str());
        if (!iter(it, end)) {
            // _param._map.pop_back();
            _param._map.push_back(c);
            return;
        }
        if (c._food == -1)
            c._food = std::stoi(it->str());
        if (!iter(it, end)) {
            // _param._map.pop_back();
            _param._map.push_back(c);
            return;
        }
        if (c._linemate == -1)
            c._linemate = std::stoi(it->str());
        if (!iter(it, end)) {
            // _param._map.pop_back();
            _param._map.push_back(c);
            return;
        }
        if (c._deraumere == -1)
            c._deraumere = std::stoi(it->str());
        if (!iter(it, end)) {
            // _param._map.pop_back();
            _param._map.push_back(c);
            return;
        }
        if (c._sibur == -1)
            c._sibur = std::stoi(it->str());
        if (!iter(it, end)) {
            // _param._map.pop_back();
            _param._map.push_back(c);
            return;
        }
        if (c._mendiane == -1)
            c._mendiane = std::stoi(it->str());
        if (!iter(it, end)) {
            // _param._map.pop_back();
            _param._map.push_back(c);
            return;
        }
        if (c._phiras == -1)
            c._phiras = std::stoi(it->str());
        if (!iter(it, end)) {
            // _param._map.pop_back();
            _param._map.push_back(c);
            return;
        }
        if (c._thystame == -1)
            c._thystame = std::stoi(it->str());
        std::cout << c._x << " " << c._y << " " << c._food << " " << c._linemate << " " << c._deraumere << " " << c._sibur << " " << c._mendiane << " " << c._phiras << " " << c._thystame << std::endl;
        // _param._map.pop_back();
        _param._map.push_back(c);
    }
} // gui