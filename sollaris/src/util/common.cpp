#include "common.h"
#include <cmath>

Vec3::Vec3() : x(0), y(0), z(0) {}

Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

Vec3::Vec3(const Vec3& b) : x(b.x), y(b.y), z(b.z) {}

Vec3::Vec3(Vec3&& b) : x(b.x), y(b.y), z(b.z) {
    b.x = 0;
    b.y = 0;
    b.z = 0;
}

Vec3::~Vec3() {};

Vec3& Vec3::operator=(const Vec3& rhs) {
    this->x = rhs.x;
    this->y = rhs.y;
    this->z = rhs.z;
    return *this;
}

Vec3& Vec3::operator=(Vec3&& rhs) {
    *this = rhs;
    rhs.x = 0;
    rhs.y = 0;
    rhs.z = 0;
    return *this;
}

double Vec3::length() const {
    Vec3 tmp = this->squared();
    return std::sqrt(tmp.x + tmp.y + tmp.z);
}

Vec3 Vec3::normalized() const {
    return *this / this->length();
}

Vec3 Vec3::squared() const {
    return (*this) * (*this);
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
