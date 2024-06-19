/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** Sleep.cpp
*/

#include "Sleep.hpp"

void Sleep::sleepInSeconds(int time)
{
    sleep(time);
}

void Sleep::sleepInMicroSecond(int time)
{
    usleep(time);
}
