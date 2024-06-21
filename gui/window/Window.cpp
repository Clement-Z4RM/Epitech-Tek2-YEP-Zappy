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

    _camera = std::make_shared<raylib::Camera3>();
    Vector3 cameraPosition = {10.0f, 10.0f, 10.0f};
    Vector3 cameraTarget = {0.0f, 0.0f, 0.0f};
    Vector3 cameraUp = {0.0f, 1.0f, 0.0f};
    float cameraFovy = 45.0f;
    Camera3D camera = {cameraPosition, cameraTarget, cameraUp, cameraFovy, CAMERA_PERSPECTIVE};
    _camera = std::make_shared<raylib::Camera3>(camera);

    raylib::Mouse::disableCursor();
}

Window::~Window() = default;

void Window::run(Parameters &params)
{
    if (!raylib::Raylib::windowShouldClose()) {
        raylib::Camera::updateCamera(_camera, raylib::CAMERA_FREE);

        if (raylib::Keyboard::isKeyPressed('Z'))
            _camera->_camera->target = Vector3{0.0f, 0.0f, 0.0f};

        raylib::Draw::beginDrawing();

        raylib::Raylib::clearBackground({255, 255, 255, 255});

        raylib::Camera::begin3DMode(_camera);

        raylib::Cube::drawCube(cubePosition, 2.0f, 2.0f, 2.0f, {255, 0, 0, 255});
        raylib::Cube::drawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, {88, 57, 39, 255});

        raylib::Camera::end3DMode();

        raylib::Rectangle::drawRectangle(10, 10, 220, 100, {102, 191, 255, 255});
        raylib::Rectangle::drawRectangleLines(10, 10, 220, 100, {0, 121, 241, 255});

        raylib::Text::drawText("Zappy", 20, 20, 10, {255, 255, 255, 255});
        raylib::Text::drawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, {80, 80, 80, 255});
        raylib::Text::drawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, {80, 80, 80, 255});
        raylib::Text::drawText("- [Z] to Zoom to (0, 0, 0)", 40, 80, 10, {80, 80, 80, 255});

        raylib::Draw::endDrawing();
    }
}
