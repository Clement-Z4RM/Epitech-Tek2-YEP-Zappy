/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** main.c
*/

#include "./modules/clients_manager/clients_manager.h"

int main(void) {
    client_manager_t *client_manager = client_manager_create();
    client_t *client = client_create(42);

    client_manager_add_client(client_manager, client);
    client_manager_remove_client(client_manager, client);
    client_manager_destroy(client_manager);
    return 0;
}
