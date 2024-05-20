cmake_minimum_required(VERSION 3.23)
project(Zappy-Server)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_compile_options(-W -Wall -Wextra -Wpedantic -Werror)

set(CMAKE_C_STANDARD 17)

include_directories(include)

add_executable(zappy_server
        src/main.c
        src/models/map.h)
