/*
** EPITECH PROJECT, 2024
** Epitech_Tek2_YEP_Zappy
** File description:
** Window.cpp
*/

#include "Window.hpp"

Window::Window()
{
    raylib::Raylib::initWindow(800, 450, "Zappy");
    raylib::Raylib::setFPS(60);

    raylib::Vector3D cameraPosition = {10.0f, 10.0f, 10.0f};
    raylib::Vector3D cameraTarget = {0.0f, 0.0f, 0.0f};
    raylib::Vector3D cameraUp = {0.0f, 1.0f, 0.0f};
    float cameraFovy = 45.0f;
    _camera = std::make_shared<raylib::Camera3D>(cameraPosition, cameraTarget, cameraUp, cameraFovy, CAMERA_PERSPECTIVE);

    raylib::Raylib::disableCursor();
}

Window::~Window() = default;

void Window::run(Parameters &params)
{
    if (!raylib::Raylib::windowShouldClose()) {
        raylib::Raylib::updateCamera(_camera, raylib::CAMERA_FREE);

        if (raylib::Raylib::isKeyPressed('Z'))
            _camera->target = raylib::Vector3D{0.0f, 0.0f, 0.0f};

        raylib::Raylib::beginDrawing();

        raylib::Raylib::clearBackground({255, 255, 255, 255});

        raylib::Raylib::begin3DMode(_camera);

        raylib::Raylib::drawCube(cubePosition, 2.0f, 2.0f, 2.0f, {255, 0, 0, 255});
        raylib::Raylib::drawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, {88, 57, 39, 255});

        raylib::Raylib::end3DMode();

        raylib::Raylib::drawRectangle(10, 10, 220, 100, {102, 191, 255, 255});
        raylib::Raylib::drawRectangleLines(10, 10, 220, 100, {0, 121, 241, 255});

        raylib::Raylib::drawText("Zappy", 20, 20, 10, {255, 255, 255, 255});
        raylib::Raylib::drawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, {80, 80, 80, 255});
        raylib::Raylib::drawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, {80, 80, 80, 255});
        raylib::Raylib::drawText("- [Z] to Zoom to (0, 0, 0)", 40, 80, 10, {80, 80, 80, 255});

        raylib::Raylib::endDrawing();
    }
}
