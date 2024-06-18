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
 * @brief ai_handler_data_t definition for circular dependency
 * with requests manager
 */
typedef struct ai_handler_data_s ai_handler_data_t;

extern void forward(ai_handler_data_t *data);

extern void right(ai_handler_data_t *data);
extern void left(ai_handler_data_t *data);

#endif /* !ZAPPY_SERVER_AI_COMMANDS_H_ */
