cmake_minimum_required(VERSION 3.23)
project(Zappy-Server)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_compile_options(-W -Wall -Wextra -Wpedantic -Werror)

set(CMAKE_C_STANDARD 17)

include_directories(include)
include_directories(src/modules)

add_executable(zappy_server
        include/macros.h
        include/utilities.h
        include/zappy_server.h
        src/main.c
        src/zappy_server.c
        src/utilities/numbers/str_to_num.c
        src/utilities/numbers/str_to_port.c
        src/utilities/strings/str_array_split.c
        src/modules/options/options.h
        src/modules/options/options.c
        src/modules/options/usage.c
        src/modules/options/parsers/unknown.c
        src/modules/options/parsers/usage.c
        src/modules/options/parsers/port.c
        src/modules/options/parsers/world_width.c
        src/modules/options/parsers/world_height.c
        src/modules/options/parsers/teams.c
        src/modules/options/parsers/clients.c
        src/modules/options/parsers/frequency.c
        src/modules/clients_manager/clients_manager.c
        src/modules/client/client.c
        src/modules/requests_manager/requests_manager.c
        src/modules/network/endpoint/endpoint.c
        src/modules/network/network.c)
