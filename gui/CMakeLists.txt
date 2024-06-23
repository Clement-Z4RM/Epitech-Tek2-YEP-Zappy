cmake_minimum_required(VERSION 3.26.4)
project(zappy_gui)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 14)

add_executable(zappy_gui
        main.cpp
        connection/Client.hpp
        connection/Client.cpp
        Parameters.hpp
        GUI/Gui.hpp
        GUI/Gui.cpp
        window/Window.hpp
        window/Window.cpp
        connection/Socket.hpp
        connection/Socket.cpp
        player/Player.hpp
        player/Player.cpp
        connection/Sleep.hpp
        connection/Sleep.cpp
        window/Modal.hpp
        window/Modal.cpp
        src/Egg/egg.hpp
        src/Egg/egg.cpp
)

target_link_libraries(zappy_gui PRIVATE sfml-graphics sfml-window sfml-system)
