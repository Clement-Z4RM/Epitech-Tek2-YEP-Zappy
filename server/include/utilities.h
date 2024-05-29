/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** utilities.h
*/

#ifndef ZAPPY_SERVER_UTILITIES_H_
    #define ZAPPY_SERVER_UTILITIES_H_

    #include <stdbool.h>
    #include "options/options.h"

extern bool usage(options_t *options);

//region Numbers
extern long str_to_num(const char *str, long min, long max, bool *error);

extern int str_to_port(const char *str);
//endregion

#endif /* !ZAPPY_SERVER_UTILITIES_H_ */
