/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** inventory.h
*/

#ifndef ZAPPY_SERVER_INVENTORY_H_
    #define ZAPPY_SERVER_INVENTORY_H_

    /**
     * @brief The size of the inventory string response.
     *
     * + 7 * <resource_name>
     * + 7 (commas)
     * + 70 (values)
     * + 12 (commas + spaces)
     * + 2 (brackets)
     * + 1 (line break)
     * + 1 (\0)
     */
    #define INVENTORY_SIZE 141

#endif /* !ZAPPY_SERVER_INVENTORY_H_ */
