cmake_minimum_required(VERSION 3.28)
project(Epitech_Tek2_YEP_Zappy)

set(CMAKE_CXX_STANDARD 14)

add_executable(Epitech_Tek2_YEP_Zappy
        main.cpp
        Client.hpp
        Client.cpp
        Parameters.hpp
        Gui.hpp
        Gui.cpp
        Window.hpp
        Window.cpp
)

target_link_libraries(Epitech_Tek2_YEP_Zappy PRIVATE config++ sfml-graphics sfml-window sfml-system)
