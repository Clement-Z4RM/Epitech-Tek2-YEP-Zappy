/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** Camera.hpp
*/

#pragma once
#include <memory>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include "Camera3D.hpp"

namespace raylib {

    class Camera {
    public:
        static void updateCamera(std::shared_ptr<raylib::Camera3> &camera, CameraMode mode);

        static void begin3DMode(std::shared_ptr<raylib::Camera3> &camera);
        static void end3DMode();
    };

}
