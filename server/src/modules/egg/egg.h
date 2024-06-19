/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** egg.h
*/

#ifndef ZAPPY_SERVER_EGG_H_
    #define ZAPPY_SERVER_EGG_H_

    #include <sys/queue.h>

/**
 * @brief Egg structure
 */
typedef struct egg_s {
    /** @brief The egg id */
    uint64_t id;
    /** @brief The next egg in the list */
    SLIST_ENTRY(egg_s) next;
} egg_t;

/**
 * @brief Eggs list
 */
SLIST_HEAD(eggs_s, egg_s);
typedef struct eggs_s eggs_t;

#endif /* !ZAPPY_SERVER_EGG_H_ */
