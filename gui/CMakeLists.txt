cmake_minimum_required(VERSION 3.26.4)
project(zappy_gui)

set(CMAKE_CXX_STANDARD 14)

add_executable(zappy_gui
        main.cpp
        Client.hpp
        Client.cpp
        Parameters.hpp
        Gui.hpp
        Gui.cpp
        Window.hpp
        Window.cpp
        src/egg.hpp
        src/egg.cpp
)

target_link_libraries(zappy_gui PRIVATE config++ sfml-graphics sfml-window sfml-system)
