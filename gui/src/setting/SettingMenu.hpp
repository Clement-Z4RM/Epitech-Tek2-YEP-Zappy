/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** SettingMenu.hpp
*/

#ifndef ZAPPY_GUI_SETTINGMENU_HPP
#define ZAPPY_GUI_SETTINGMENU_HPP

#include <iostream>

class button {
public:
    button() = default;
    ~button() = default;
    void displayButton();
private:
    std::string _name;

};

class SettingMenu {
public:
    SettingMenu() = default;
    ~SettingMenu() = default;
    void displaySettingMenu();
private:

};

#endif //ZAPPY_GUI_SETTINGMENU_HPP
