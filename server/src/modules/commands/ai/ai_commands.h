/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** ai_commands.h
*/

#ifndef ZAPPY_SERVER_AI_COMMANDS_H_
    #define ZAPPY_SERVER_AI_COMMANDS_H_

    #include "requests_manager/requests_manager.h"

    /**
     * + 7 * <resource_name>
     * + 7 (commas)
     * + 70 (values)
     * + 12 (commas + spaces)
     * + 2 (brackets)
     * + 1 (line break)
     * + 1 (\0)
     */
    #define INVENTORY_SIZE 141

/**
 * @brief ai_handler_data_t definition for circular dependency
 * with requests manager
 */
typedef struct ai_handler_data_s ai_handler_data_t;

// TODO: time (and send response at end)

extern void forward(ai_handler_data_t *data);

extern void right(ai_handler_data_t *data);
extern void left(ai_handler_data_t *data);

extern void inventory(ai_handler_data_t *data);

extern void take(ai_handler_data_t *data);

extern void set(ai_handler_data_t *data);

#endif /* !ZAPPY_SERVER_AI_COMMANDS_H_ */
