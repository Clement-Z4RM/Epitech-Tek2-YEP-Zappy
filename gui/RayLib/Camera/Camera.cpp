/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** Camera.cpp
*/

#include "Camera.hpp"

void raylib::Camera::updateCamera(std::shared_ptr<raylib::Camera3> &camera, CameraMode mode) {
    UpdateCamera(camera->_camera.get(), mode);
}

void raylib::Camera::begin3DMode(std::shared_ptr<raylib::Camera3> &camera) {
    BeginMode3D(*camera->_camera);
}

void raylib::Camera::end3DMode() {
    EndMode3D();
}
