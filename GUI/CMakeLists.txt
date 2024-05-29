cmake_minimum_required(VERSION 3.26.4x)
project(zappy_gui)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

include_directories(src)

add_executable(zappy_gui
        main.cpp
)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
target_link_libraries(zappy_gui PRIVATE sfml-graphics sfml-audio)
