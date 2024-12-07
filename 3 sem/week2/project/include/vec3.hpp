#ifndef VEC3_H
#define VEC3_H

#include <string>
#include <iostream>
#include <sstream>
#include <cmath>

class Vec3 {
public:
    Vec3(): val_x(0.), val_y(0.), val_z(0.) {};
    Vec3(double x_, double y_, double z_)
    : val_x(x_), val_y(y_), val_z(z_) {}

    double x() const {
        return val_x;
    }
    double y() const {
        return val_y;
    }
    double z() const {
        return val_z;
    }
    double get(int idx) {
        if (idx == 1) return val_x;
        else if (idx == 2) return val_y;
        else if (idx == 3) return val_z;
        else return 0;
    }
    Vec3 add(Vec3 vec) {
        val_x += vec.x();
        val_y += vec.y();
        val_z += vec.z();
        return *this;
    }
    Vec3 sub(Vec3 vec) {
        val_x -= vec.x();
        val_y -= vec.y();
        val_z -= vec.z();
        return *this;
    }
    double dot(Vec3 vec) {
        return (
        val_x * vec.x() +
        val_y * vec.y() +
        val_z * vec.z()
        );
    }
    Vec3 cross(Vec3 vec) {
        return Vec3(
            val_y * vec.z() - val_z * vec.y(), 
            -(val_x * vec.z() - val_z * vec.x()),
            val_x * vec.y() - val_y * vec.x()
        );
    }
    std::string print() {
        std::ostringstream oss;
        oss << val_x << ' ' << val_y << ' ' << val_z << '\n';
        return oss.str();
    }
    double length() {
        return pow(pow(val_x, 2) + pow(val_y, 2) + pow(val_z, 2), 0.5);
    }
    double length_squared() {
        return (pow(val_x, 2) + pow(val_y, 2) + pow(val_z, 2));
    }

private:
    double val_x, val_y, val_z;
};

#endif