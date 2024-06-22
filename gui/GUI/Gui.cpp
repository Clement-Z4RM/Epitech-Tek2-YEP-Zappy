//
// Created by mzucchero on 6/3/24.
//

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
            while (_client.isReady() && _client.isParamGet) {
                _client.readSocket();
                _client.parseMsg(_client.tmp);
            }
            std::cout << "Got all parameters" << std::endl;
            _client.parseParameters();
        }

        GUI::~GUI() = default;

        void GUI::run()
        {
            _client.getParam().windowWidth = _window.getWindowWidth();
            _client.getParam().windowHeight = _window.getWindowHeight();
            while (_window.isOpen()) {
                _client.refreshMap();
                _window.rendMap(_client.getParam());
                _window.run(_client.getParam());
            }
        }
} // gui