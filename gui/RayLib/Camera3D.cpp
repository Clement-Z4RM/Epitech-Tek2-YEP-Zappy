//
// Created by mzucchero on 6/21/24.
//

#include "Camera3D.hpp"

namespace raylib {

        Vector3D::Vector3D(float x, float y, float z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        Camera3D::Camera3D(Vector3D position, Vector3D target, Vector3D up, float fovy, int projection)
        {
            this->position = position;
            this->target = target;
            this->up = up;
            this->fovy = fovy;
            this->projection = projection;
        }
} // raylib