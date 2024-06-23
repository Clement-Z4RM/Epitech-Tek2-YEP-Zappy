/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** mct event
*/

#include "commands/gui/gui_commands.h"
#include "requests_manager/requests_manager.h"

void mct_event(gui_client_node_t *client, updater_t *updater)
{
    gui_handler_data_t data = {0};

    data.updater = updater;
    data.gui_client = client;
    mct(&data);
}
