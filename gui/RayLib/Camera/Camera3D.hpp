/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** Camera3D.hpp
*/

#pragma once
#include <memory>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"

namespace raylib {

    typedef enum {
        CAMERA_CUSTOM = 0,              // Camera custom, controlled by user (UpdateCamera() does nothing)
        CAMERA_FREE,                    // Camera free mode
        CAMERA_ORBITAL,                 // Camera orbital, around target, zoom supported
        CAMERA_FIRST_PERSON,            // Camera first person
        CAMERA_THIRD_PERSON             // Camera third person
    } CameraMode;

    class Vector3D {
    public:
        Vector3D() = default;
        Vector3D(Vector3 vec);
        ~Vector3D() = default;

        std::shared_ptr<Vector3> _vec;
    };

    class Camera3 {
    public:
        Camera3() = default;
        explicit Camera3(Camera3D camera);
        ~Camera3() = default;

        std::shared_ptr<Camera3D> _camera;
    };

} // raylib
