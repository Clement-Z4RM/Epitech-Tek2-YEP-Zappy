//
// Created by mzucchero on 6/3/24.
//

#include "Gui.hpp"

namespace gui {

        GUI::GUI(std::string &ip, std::string &port) : _client(ip, atoi(port.c_str()))
        {
            _client.readSocket();
            if (!_client.isConnected)
                exit(84);
            std::string id = "GRAPHIC\n";
            _client.sendMsg(id);
            while (_client.isReady() && _client.isParamGet) {
                _client.readSocket();
            }
            std::cout << "Got all parameters" << std::endl;
            _client.parseMap();
        }

        GUI::~GUI() = default;

        void GUI::run()
        {
            _window.rendMap(_client.getParam());
            _window.run();
        }
} // gui