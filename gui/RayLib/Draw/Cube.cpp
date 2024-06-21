//
// Created by mzucchero on 6/21/24.
//

#include "Cube.hpp"

namespace raylib {
    void Cube::drawCube(Vector3 position, float width, float height, float length, Color color) {
        Vector3 tmpPos = {position.x, position.y, position.z};
        DrawCube(tmpPos, width, height, length, color);
    }

    void Cube::drawCubeWires(Vector3 position, float width, float height, float length, Color color) {
        Vector3 tmpPos = {position.x, position.y, position.z};
        DrawCubeWires(tmpPos, width, height, length, color);
    }
} // raylib