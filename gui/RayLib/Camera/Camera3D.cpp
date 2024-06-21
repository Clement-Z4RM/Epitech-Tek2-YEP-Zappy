//
// Created by mzucchero on 6/21/24.
//

#include "Camera3D.hpp"

namespace raylib {

        Vector3D::Vector3D(Vector3 vec)
        {
            _vec = std::make_shared<Vector3>(vec);
        }

        Camera3::Camera3(Camera3D camera)
        {
            _camera = std::make_shared<Camera3D>(camera);
        }
} // raylib