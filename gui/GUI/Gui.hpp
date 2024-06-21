//
// Created by mzucchero on 6/3/24.
//

#pragma once
#include "../connection/Client.hpp"
#include "../window/Window.hpp"

namespace gui {

    class GUI {
    public:
        GUI(std::string &ip, std::string &port);
        ~GUI();
        gui::Client &getClient() { return _client; }

        void run();

    private:
        gui::Client _client;
        Window _window;
    };

} // gui
