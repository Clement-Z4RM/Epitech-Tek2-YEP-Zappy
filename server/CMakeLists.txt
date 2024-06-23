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

        #region Global structure definitions
        include/coords.h
        include/eggs.h
        include/angle_direction.h
        #endregion

        #region Main files
        src/main.c
        src/zappy_server.c
        #endregion

        #region Server module
        src/modules/server/server.h
        src/modules/server/server.c
        #endregion

        #region Utilities
        src/utilities/numbers/str_to_num.c
        src/utilities/numbers/str_to_port.c
        src/utilities/strings/remove_newline.c
        src/utilities/strings/str_array_split.c
        src/utilities/strings/free_double_tab.c
        src/utilities/time/mstime.c
        src/utilities/signals/catch_signal.c
        src/utilities/network/send_string.c
        #endregion

        #region Modules
        #region Logs module
        src/modules/logs/logs.h
        src/modules/logs/logs_colors.h
        src/modules/logs/successes/logs_successes.h
        src/modules/logs/successes/network_successes_logs.c
        src/modules/logs/successes/team_successes_logs.c
        src/modules/logs/failures/logs_failures.h
        src/modules/logs/failures/request_failures_logs.c
        src/modules/logs/failures/team_failures_logs.c
        src/modules/logs/successes/gui_handlers/tna_success.c
        src/modules/logs/failures/gui_handlers/sst_failure.c
        src/modules/logs/successes/gui_handlers/sst_success.c
        src/modules/logs/successes/gui_handlers/sgt_success.c
        src/modules/logs/successes/gui_handlers/ppo_success.c
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
        src/modules/player/player_methods.h
        src/modules/player/player.c
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
        src/modules/clients_manager/helpers/getters.c
        src/modules/clients_manager/helpers/team.c
        src/modules/clients_manager/helpers/eggs.c
        #endregion

        #region Requests manager module
        src/modules/requests_manager/requests_manager.h
        src/modules/requests_manager/requests_manager.c
        #endregion

        #region Commands module
        src/modules/commands/commands.h
        src/modules/commands/gui/gui_commands.h
        src/modules/commands/gui/handlers/msz.c
        src/modules/commands/gui/handlers/sst.c
        src/modules/commands/gui/handlers/sgt.c
        src/modules/commands/gui/handlers/pin.c
        src/modules/commands/gui/handlers/ppo.c
        src/modules/commands/gui/handlers/tna.c
        src/modules/commands/gui/handlers/bct.c
        src/modules/commands/gui/handlers/mct.c
        src/modules/commands/gui/handlers/plv.c
        src/modules/commands/gui/events/pex.c
        src/modules/commands/gui/events/pbc.c
        src/modules/commands/gui/events/plv_event.c
        src/modules/commands/gui/events/pnw.c
        src/modules/commands/gui/events/pfk.c
        src/modules/commands/gui/events/pdr.c
        src/modules/commands/gui/events/smg.c
        src/modules/commands/gui/events/seg.c
        src/modules/commands/gui/events/pgt.c
        src/modules/commands/gui/events/pdi.c
        src/modules/commands/gui/events/pic.c
        src/modules/commands/gui/events/enw.c
        src/modules/commands/gui/events/sbp.c
        src/modules/commands/gui/events/edi.c
        src/modules/commands/gui/events/ebo.c
        src/modules/commands/gui/events/ppo_event.c
        src/modules/logs/successes/events/pdi_success.c
        src/modules/logs/successes/events/forward_success.c
        src/modules/logs/successes/events/broadcast_success.c
        src/modules/logs/successes/events/look_success.c
        src/modules/logs/successes/events/turn_success.c
        src/modules/logs/successes/events/set_success.c
        src/modules/logs/successes/events/take_success.c
        src/modules/logs/successes/events/fork_success.c
        src/modules/commands/ai/ai_commands.h
        src/modules/commands/ai/forward.c
        src/modules/commands/ai/turn.c
        src/modules/commands/ai/look/look.h
        src/modules/commands/ai/look/look.c
        src/modules/commands/ai/look/look_fill_buffer.c
        src/modules/commands/ai/look/look_directions.c
        src/modules/commands/ai/inventory.h
        src/modules/commands/ai/inventory.c
        src/modules/commands/ai/broadcast.c
        src/modules/commands/ai/connect_nbr.c
        src/modules/commands/ai/fork.c
        src/modules/commands/ai/take.c
        src/modules/commands/ai/set.c
        src/modules/commands/ai/incantation/incantation.h
        src/modules/commands/ai/incantation/incantation.c
        src/modules/commands/ai/incantation/start.c
        src/modules/commands/ai/incantation/helpers/player.c
        src/modules/commands/ai/incantation/helpers/resource.c
        #endregion

        #region Updater module
        src/modules/updater/updater.h
        src/modules/updater/updater.c
        src/modules/updater/command_updater.c
        src/modules/commands/gui/handlers/enw_handler.c
        src/modules/commands/gui/events/pie.c
        #endregion
        #endregion
        src/modules/commands/gui/events/mct_event.c
)

target_link_libraries(zappy_server PRIVATE m)
