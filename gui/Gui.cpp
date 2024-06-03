//
// Created by mzucchero on 6/3/24.
//

#include "Gui.hpp"

namespace gui {

        GUI::GUI(std::string &ip, std::string &port) : _graphic(ip, atoi(port.c_str()))
        {
            _graphic.readSocket();
            if (!_graphic.isConnected)
                exit(84);
            std::string id = "GRAPHIC\n";
            _graphic.sendMsg(id);
            while (_graphic.isReady() && _graphic.getParam) {
                _graphic.readSocket();
            }
            std::cout << "Got all parameters" << std::endl;
        }

        GUI::~GUI() = default;

        void GUI::run()
        {
            for (auto &i : _graphic.getMap()) {
                std::cout << i << std::endl;
            }
        }
} // gui