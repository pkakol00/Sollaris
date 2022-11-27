#include "common.h"
#include <cmath>

double Vec3::length() const {
    Vec3 tmp = square(*this);
    return std::sqrt(tmp.x + tmp.y + tmp.z);
}
Vec3 Vec3::normalized() const {
    return *this / this->length();
}

Vec3& Vec3::operator+=(const Vec3& rhs) {
    this->x += rhs.x;
    this->y += rhs.y;
    this->z += rhs.z;

    return *this;
}
Vec3& Vec3::operator-=(const Vec3& rhs) {
    this->x -= rhs.x;
    this->y -= rhs.y;
    this->z -= rhs.z;

    return *this;
}
Vec3& Vec3::operator*=(const Vec3& rhs) {
    this->x *= rhs.x;
    this->y *= rhs.y;
    this->z *= rhs.z;

    return *this;
}
Vec3& Vec3::operator/=(const Vec3& rhs) {
    this->x /= rhs.x;
    this->y /= rhs.y;
    this->z /= rhs.z;

    return *this;
}

Vec3& Vec3::operator+=(const double& rhs) {
    this->x += rhs;
    this->y += rhs;
    this->z += rhs;
    return *this;
}
Vec3& Vec3::operator-=(const double& rhs) {
    this->x -= rhs;
    this->y -= rhs;
    this->z -= rhs;
    return *this;
}
Vec3& Vec3::operator*=(const double& rhs) {
    this->x *= rhs;
    this->y *= rhs;
    this->z *= rhs;
    return *this;
}
Vec3& Vec3::operator/=(const double& rhs) {
    this->x /= rhs;
    this->y /= rhs;
    this->z /= rhs;
    return *this;
}

Vec3 Vec3::operator+() const {
    return *this;
}
Vec3 Vec3::operator-() const {
    return (*this) * -1;
}

Vec3 square(Vec3 lhs) {
    return lhs * lhs;
}

Vec3 operator+(Vec3 lhs, const Vec3& rhs) {
    return lhs += rhs;
}
Vec3 operator-(Vec3 lhs, const Vec3& rhs) {
    return lhs -= rhs;
}
Vec3 operator*(Vec3 lhs, const Vec3& rhs) {
    return lhs *= rhs;
}
Vec3 operator/(Vec3 lhs, const Vec3& rhs) {
    return lhs /= rhs;
}

Vec3 operator+(Vec3 lhs, const double& rhs) {
    return lhs += rhs;
}
Vec3 operator-(Vec3 lhs, const double& rhs) {
    return lhs -= rhs;
}
Vec3 operator*(Vec3 lhs, const double& rhs) {
    return lhs *= rhs;
}
Vec3 operator/(Vec3 lhs, const double& rhs) {
    return lhs /= rhs;
}
