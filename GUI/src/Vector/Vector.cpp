/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Vector.cpp
*/

#include "Vector.hpp"

namespace Math {

        Vector3D::Vector3D(double x_pos, double y_pos, double z_pos) : x(x_pos), y(y_pos), z(z_pos) {}

        Vector3D::Vector3D(Vector3D&& other) noexcept : x(other.x), y(other.y), z(other.z) {}

        double Vector3D::length() const
        {
            return std::sqrt(x * x + y * y + z * z);
        }

        double Vector3D::dot(Vector3D vector) const
        {
            return x * vector.x + y * vector.y + z * vector.z;
        }

        void Vector3D::rotateY(double angle)
        {
            double x_tmp = x;
            double z_tmp = z;
            x = x_tmp * std::cos(angle) + z_tmp * std::sin(angle);
            z = -x_tmp * std::sin(angle) + z_tmp * std::cos(angle);
        }

        void Vector3D::rotateX(double angle)
        {
            double y_tmp = y;
            double z_tmp = z;
            y = y_tmp * std::cos(angle) - z_tmp * std::sin(angle);
            z = y_tmp * std::sin(angle) + z_tmp * std::cos(angle);
        }

        Vector3D Vector3D::reflect(const Vector3D& normal) const {
            double dotProduct = dot(normal);
            Vector3D tmp = normal * 2.0 * dotProduct;
            Vector3D reflectedVector = *this - tmp;

            return reflectedVector;
        }


        std::ostream& operator<<(std::ostream& os, const Vector3D& vector) {
            os << "Vector(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
            return os;
        }
} // raytracer
