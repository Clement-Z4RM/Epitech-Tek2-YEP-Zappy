/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** resource.h
*/

#ifndef ZAPPY_SERVER_RESOURCE_H_
    #define ZAPPY_SERVER_RESOURCE_H_

    #include <sys/queue.h>
    #include <stddef.h>

/**
 * @brief The type of a resource
 */
typedef enum resource_type_e {
    RT_FOOD,
    RT_STONE
} resource_type_t;

/**
 * @brief The name of a resource
 */
typedef enum resource_name_e {
    RN_FOOD,
    RN_LINEMATE,
    RN_DERAUMERE,
    RN_SIBUR,
    RN_MENDIANE,
    RN_PHIRAS,
    RN_THYSTAME,
    RESOURCES_COUNT
} resource_name_t;

/**
 * @brief Resource structure
 */
typedef struct resource_s {
    /** @brief The name of the resource */
    resource_name_t name;
    /** @brief The type of the resource */
    resource_type_t type;
    /** @brief The density of the resource */
    float density;
} resource_t;

/**
 * @brief The density of each resource
 */
static const resource_t RESOURCES[RESOURCES_COUNT] = {
    [RN_FOOD] = {RN_FOOD, RT_FOOD, 0.5f},
    [RN_LINEMATE] = {RN_LINEMATE, RT_STONE, 0.3f},
    [RN_DERAUMERE] = {RN_DERAUMERE, RT_STONE, 0.15f},
    [RN_SIBUR] = {RN_SIBUR, RT_STONE, 0.1f},
    [RN_MENDIANE] = {RN_MENDIANE, RT_STONE, 0.1f},
    [RN_PHIRAS] = {RN_PHIRAS, RT_STONE, 0.08f},
    [RN_THYSTAME] = {RN_THYSTAME, RT_STONE, 0.05f}
};

/**
 * @brief The name of each resource as a string
 */
static const char *RESOURCE_NAMES[RESOURCES_COUNT] = {
    NULL,
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame"
};

#endif /* !ZAPPY_SERVER_RESOURCE_H_ */
