/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** Sleep.hpp
*/

#pragma once
#include <unistd.h>

class Sleep {
public:
    /**
     * @brief Sleep for a given time in seconds
     * @param time
     */
    static void sleepInSeconds(int time);

    /**
     * @brief Sleep for a given time in microseconds
     * @param time
     */
    static void sleepInMicroSecond(int time);
};
