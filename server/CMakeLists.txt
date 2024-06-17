cmake_minimum_required(VERSION 3.23)
project(Zappy-Server)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_compile_options(-W -Wall -Wextra -Wpedantic -Werror)

set(CMAKE_C_STANDARD 17)

include_directories(include)
include_directories(src/modules)

add_executable(zappy_server
        #region Global headers
        include/macros.h
        include/utilities.h
        include/zappy_server.h
        include/responses.h
        #endregion

        #region Main files
        src/main.c
        src/zappy_server.c
        #endregion

        #region Utilities
        src/utilities/numbers/str_to_num.c
        src/utilities/numbers/str_to_port.c
        src/utilities/strings/remove_newline.c
        src/utilities/strings/str_array_split.c
        src/utilities/strings/free_double_tab.c
        src/utilities/signals/catch_signal.c
        #endregion

        #region Modules
        #region Logs module
        src/modules/logs/logs.h
        src/modules/logs/logs_colors.h
        src/modules/logs/successes/logs_successes.h
        src/modules/logs/successes/network_successes_logs.c
        src/modules/logs/failures/logs_failures.h
        src/modules/logs/failures/request_failures_logs.c
        #endregion

        #region Options module
        src/modules/options/options.h
        src/modules/options/options.c
        src/modules/options/usage.c
        src/modules/options/parsers/usage.c
        src/modules/options/parsers/world_height.c
        src/modules/options/parsers/clients.c
        src/modules/options/parsers/teams.c
        src/modules/options/parsers/unknown.c
        src/modules/options/parsers/frequency.c
        src/modules/options/parsers/world_width.c
        src/modules/options/parsers/port.c
        #endregion

        #region Egg module
        src/modules/egg/egg.h
        #endregion

        #region Player module
        src/modules/player/player.h
        #endregion

        #region Resource module
        src/modules/resource/resource.h
        #endregion

        #region Map module
        src/modules/map/map.h
        src/modules/map/map.c
        src/modules/map/helpers/resource.c
        #endregion

        #region Network module
        src/modules/network/network.h
        src/modules/network/network.c
        src/modules/network/endpoint/endpoint.h
        src/modules/network/endpoint/endpoint.c
        #endregion

        #region Client module
        src/modules/client/client.h
        src/modules/client/client.c
        #endregion

        #region Clients manager module
        src/modules/clients_manager/clients_manager.h
        src/modules/clients_manager/clients_manager.c
        #endregion

        #region Requests manager module
        src/modules/requests_manager/requests_manager.h
        src/modules/requests_manager/requests_manager.c
        src/modules/commands/commands.h
        src/modules/commands/gui/msz.c
        src/modules/logs/failures/team_failures_logs.c
        src/modules/logs/successes/team_successes_logs.c
        src/modules/commands/gui/gui_commands.h
        #endregion
        #endregion
)
