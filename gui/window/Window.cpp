/*
** EPITECH PROJECT, 2024
** Epitech_Tek2_YEP_Zappy
** File description:
** Window.cpp
*/

#include "Window.hpp"

Window::Window()
{
    raylib::Raylib::initWindow(1920, 1080, "Zappy");
    raylib::Raylib::setFPS(60);

    _camera = std::make_shared<raylib::Camera3>();
    Vector3 cameraPosition = {27.0f, 18.0f, 27.0f};
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

        raylib::Draw::beginDrawing();

        raylib::Raylib::clearBackground({255, 255, 255, 255});

        std::cout << params._players.size() << std::endl;

        this->renderMap(params);
        this->information(params);

        raylib::Draw::endDrawing();
    }
}

void Window::renderMap(Parameters &params)
{
    raylib::Camera::begin3DMode(_camera);

    for (float z = 0; z < params._height + 1; z++) {
        for (float x = 0; x < params._width + 1; x++) {
            raylib::Cube::drawCube({x, 0.0f, z}, 1.0f, 1.0f, 1.0f, {0, 153, 0, 255});
            raylib::Cube::drawCubeWires({x, 0.0f, z}, 1.0f, 1.0f, 1.0f, {51, 51, 0, 255});
        }
    }

//    if (!params._players.empty()) {
        raylib::Cube::drawCube({16, 1.0f, 16}, 1.0f, 1.0f, 1.0f, {0, 0, 255, 255});
        raylib::Cube::drawCubeWires({16, 1.0f, 16}, 1.0f, 1.0f, 1.0f, {51, 51, 0, 255});
//    }

    raylib::Camera::end3DMode();
}

void Window::information(Parameters &params)
{
    raylib::Rectangle::drawRectangle(10, 10, 220, 100, {102, 191, 255, 255});
    raylib::Rectangle::drawRectangleLines(10, 10, 220, 100, {0, 121, 241, 255});

    Vector3 pos = _camera->_camera->position;
    std::string posStr = "Actual Pos: " + std::to_string(pos.x) + " " + std::to_string(pos.y) + " " + std::to_string(pos.z);
    raylib::Text::drawText("Zappy", 20, 20, 10, {255, 255, 255, 255});
    raylib::Text::drawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, {80, 80, 80, 255});
    raylib::Text::drawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, {80, 80, 80, 255});
    raylib::Text::drawText("- [Z] to Zoom to (0, 0, 0)", 40, 80, 10, {80, 80, 80, 255});
    raylib::Text::drawText(posStr, 40, 100, 10, {80, 80, 80, 255});
}

void Window::displayPlayers(Parameters &params)
{
//    for (auto &player : params._players) {

//    }
}
