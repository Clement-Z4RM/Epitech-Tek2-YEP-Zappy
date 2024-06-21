/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** Raylib.hpp
*/

#pragma once
#include <memory>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include "Camera3D.hpp"

namespace raylib {

    class Raylib {
    public:
        static void initWindow(int width, int height, const char *title);
        static bool windowShouldClose();

        static void setFPS(int fps);

        static bool isKeyPressed(int key);
        static bool isMouseButtonDown(int button);
        static float getMouseWheelMove();
        static void disableCursor();

        static void updateCamera(std::shared_ptr<Camera3D> &camera, CameraMode mode);

        static void beginDrawing();
        static void endDrawing();

        static void clearBackground(Color color);

        static void begin3DMode(std::shared_ptr<raylib::Camera3D> &camera);
        static void end3DMode();

        static void drawCube(Vector3D position, float width, float height, float length, Color color);
        static void drawCubeWires(Vector3D position, float width, float height, float length, Color color);

        static void drawGrid(int slices, float spacing);

        static void drawRectangle(int x, int y, int width, int height, Color color);
        static void drawRectangleLines(int x, int y, int width, int height, Color color);

        static void drawText(const char *text, int x, int y, int fontSize, Color color);
    };

}