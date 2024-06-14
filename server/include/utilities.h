/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** utilities.h
*/

#ifndef ZAPPY_SERVER_UTILITIES_H_
    #define ZAPPY_SERVER_UTILITIES_H_

    #include <stdbool.h>

//region Numbers
extern long str_to_num(const char *str, long min, long max, bool *error);

extern int str_to_port(const char *str);
//endregion

//region Strings
extern char **str_array_split(char *str, char *separator);
//endregion

//region Signals
extern void catch_signal(int signum, void (*handler)(int));
//endregion

#endif /* !ZAPPY_SERVER_UTILITIES_H_ */
