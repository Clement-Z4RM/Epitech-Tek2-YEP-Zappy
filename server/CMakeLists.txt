cmake_minimum_required(VERSION 3.23)
project(Zappy-Server)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_compile_options(-W -Wall -Wextra -Wpedantic -Werror)

set(CMAKE_C_STANDARD 17)

include_directories(include)

add_executable(zappy_server
        include/macros.h
        src/main.c
        src/modules/options/options.c
        src/modules/options/options.h
        src/modules/options/parsers/unknown.c
        src/modules/options/parsers/usage.c
        src/modules/options/parsers/port.c
        src/modules/options/parsers/world_width.c
        src/modules/options/parsers/world_height.c
        src/modules/options/parsers/teams.c
        src/modules/options/parsers/clients.c
        src/modules/options/parsers/frequency.c)
