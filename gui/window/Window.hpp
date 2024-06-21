/*
** EPITECH PROJECT, 2024
** Epitech_Tek2_YEP_Zappy
** File description:
** Window.hpp
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <deque>
#include <memory>
#include <iostream>
#include <unordered_map>
#include "../Parameters.hpp"
#include "Modal.hpp"
#include "../RayLib/Raylib.hpp"

class Window {
public:
    Window();
    ~Window();

    void run(Parameters &params);

private:
    std::shared_ptr<raylib::Camera3D> _camera{};
    raylib::Vector3D cubePosition = {0.0f, 0.0f, 0.0f};
};
