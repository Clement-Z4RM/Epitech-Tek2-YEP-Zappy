/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Vector.hpp
*/

#pragma once
#include <cmath>
#include <iostream>

namespace Math {

    class Vector3D {
    public:
        Vector3D() = default;
        Vector3D(double x_pos, double y_pos, double z_pos);
        Vector3D(Vector3D&& other) noexcept;
        Vector3D(const Vector3D& other) = default;
        ~Vector3D() = default;

        double x {0};
        double y {0};
        double z {0};

        double length() const;
        double dot(Vector3D vector) const;

        void rotateY(double angle);
        void rotateX(double angle);

        Vector3D& operator=(const Vector3D& other) {
            x = other.x;
            y = other.y;
            z = other.z;
            return *this;
        }

        Vector3D operator+(const Vector3D& other) const {
            return {x + other.x, y + other.y, z + other.z};
        }

        Vector3D& operator+=(const Vector3D& other) {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        Vector3D operator-(const Vector3D& other) const {
            return {x - other.x, y - other.y, z - other.z};
        }

        Vector3D& operator-=(const Vector3D& other) {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return *this;
        }

        Vector3D operator*(double scalar) const {
            return {x * scalar, y * scalar, z * scalar};
        }

        Vector3D& operator*=(double scalar) {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }

        Vector3D operator/(double scalar) const {
            return {x / scalar, y / scalar, z / scalar};
        }

        Vector3D& operator/=(double scalar) {
            x /= scalar;
            y /= scalar;
            z /= scalar;
            return *this;
        }

        void normalize() {
            double len = length();
            if (len != 0) {
                x /= len;
                y /= len;
                z /= len;
            }
        }

        Vector3D reflect(const Vector3D& normal) const;
    };
    std::ostream& operator<<(std::ostream& os, const Vector3D& vector);

} // raytracer
