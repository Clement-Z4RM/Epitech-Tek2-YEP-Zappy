//
// Created by mzucchero on 6/3/24.
//

#pragma once
#include "Client.hpp"
#include "Window.hpp"

namespace gui {

    class GUI {
    public:
        GUI(std::string &ip, std::string &port);
        ~GUI();

        void run();

    private:
        gui::Client _client;
        Window _window;
    };

} // gui
