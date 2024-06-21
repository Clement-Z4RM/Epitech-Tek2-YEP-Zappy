/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** Camera3D.hpp
*/

#pragma once

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
        Vector3D(float x, float y, float z);
        ~Vector3D() = default;

        float x;
        float y;
        float z;
    };

    class Camera3D {
    public:
        Camera3D() = default;
        Camera3D(Vector3D position, Vector3D target, Vector3D up, float fovy, int projection);
        ~Camera3D() = default;

        Vector3D position{};
        Vector3D target{};
        Vector3D up{};
        float fovy;
        int projection;
    };

} // raylib
