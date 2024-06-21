/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** Raylib.cpp
*/

#include "Raylib.hpp"

namespace raylib {

    void Raylib::initWindow(int width, int height, const char *title) {
        InitWindow(width, height, title);
    }

    void Raylib::setFPS(int fps) {
        SetTargetFPS(fps);
    }

    bool Raylib::windowShouldClose() {
        return WindowShouldClose();
    }

    bool Raylib::isKeyPressed(int key) {
        return IsKeyPressed(key);
    }

    bool Raylib::isMouseButtonDown(int button) {
        return IsMouseButtonDown(button);
    }

    float Raylib::getMouseWheelMove() {
        return GetMouseWheelMove();
    }

    void Raylib::disableCursor() {
        DisableCursor();
    }

    void Raylib::beginDrawing() {
        BeginDrawing();
    }

    void Raylib::endDrawing() {
        EndDrawing();
    }

    void Raylib::end3DMode() {
        EndMode3D();
    }

    void Raylib::drawCube(Vector3D position, float width, float height, float length, Color color) {
        Vector3 tmpPos = {position.x, position.y, position.z};
        DrawCube(tmpPos, width, height, length, color);
    }

    void Raylib::drawCubeWires(Vector3D position, float width, float height, float length, Color color) {
        Vector3 tmpPos = {position.x, position.y, position.z};
        DrawCubeWires(tmpPos, width, height, length, color);
    }

    void Raylib::clearBackground(Color color) {
        ClearBackground(color);
    }

    void Raylib::drawGrid(int slices, float spacing) {
        DrawGrid(slices, spacing);
    }

    void Raylib::drawRectangle(int x, int y, int width, int height, Color color) {
        DrawRectangle(x, y, width, height, color);
    }

    void Raylib::drawRectangleLines(int x, int y, int width, int height, Color color) {
        DrawRectangleLines(x, y, width, height, color);
    }

    void Raylib::drawText(const char *text, int x, int y, int fontSize, Color color) {
        DrawText(text, x, y, fontSize, color);
    }
}

void raylib::Raylib::updateCamera(std::shared_ptr<raylib::Camera3D> &camera, CameraMode mode) {
    Camera tmpCam = {0};
    tmpCam.position = {camera->position.x, camera->position.y, camera->position.z};
    tmpCam.target = {camera->target.x, camera->target.y, camera->target.z};
    tmpCam.up = {camera->up.x, camera->up.y, camera->up.z};
    tmpCam.fovy = camera->fovy;
    tmpCam.projection = camera->projection;
    UpdateCamera(&tmpCam, mode);
}

void raylib::Raylib::begin3DMode(std::shared_ptr<raylib::Camera3D> &camera) {
    Camera tmpCam = {0};
    tmpCam.position = {camera->position.x, camera->position.y, camera->position.z};
    tmpCam.target = {camera->target.x, camera->target.y, camera->target.z};
    tmpCam.up = {camera->up.x, camera->up.y, camera->up.z};
    tmpCam.fovy = camera->fovy;
    tmpCam.projection = camera->projection;
    BeginMode3D(tmpCam);
}