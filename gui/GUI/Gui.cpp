/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** Gui.cpp
*/

#include "Gui.hpp"

namespace gui {

        GUI::GUI(std::string &ip, std::string &port) : _client(ip, atoi(port.c_str()))
        {
            _client.readSocket();
            _client.parseMsg(_client.tmp);
            if (!_client.isConnected)
                throw std::runtime_error("Connection failed");
            std::string id = "GRAPHIC\n";
            _client.sendMsg(id);
            while (_client.isParamGet && _client.getParam()._eggs.getEggs().empty()) {
                _client.readSocket();
                _client.parseMsg(_client.tmp);
            }
            std::cout << "Got all parameters" << std::endl;
            _client.parseParameters();
        }

        GUI::~GUI() = default;

        void GUI::run()
        {
            while (!raylib::Raylib::windowShouldClose()) {
                _client.refreshMap();
                _window.run(_client.getParam());
            }
        }
} // gui