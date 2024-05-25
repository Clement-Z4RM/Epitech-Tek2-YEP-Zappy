/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** utilities.h
*/

#ifndef ZAPPY_SERVER_UTILITIES_H_
    #define ZAPPY_SERVER_UTILITIES_H_

    #include <stdbool.h>

extern long str_to_num(const char *str, long min, long max, bool *error);

extern int str_to_port(const char *str);

#endif /* !ZAPPY_SERVER_UTILITIES_H_ */
