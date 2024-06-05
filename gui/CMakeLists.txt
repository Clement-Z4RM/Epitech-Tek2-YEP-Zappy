cmake_minimum_required(VERSION 3.26.4)
project(zappy_gui)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

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
        Socket.hpp
)

target_link_libraries(zappy_gui PRIVATE sfml-graphics sfml-window sfml-system)
