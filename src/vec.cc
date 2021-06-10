#include "../include/vec.h"

float* Vec3::Data() { return new float[3]{ x, y, z }; }

float Vec3::Mag() { return std::sqrt(x * x + y * y + z * z); }

Vec3 Vec3::operator+(const Vec3& rhs) const {
	return Vec3(x + rhs.x, y + rhs.y, z + rhs.z);
}
Vec3 Vec3::operator-(const Vec3& rhs) const {
	return Vec3(x - rhs.x, y - rhs.y, z - rhs.z);
}
Vec3 Vec3::operator*(const Vec3& rhs) const {
	return Vec3(x * rhs.x, y * rhs.y, z * rhs.z);
}
Vec3 Vec3::operator/(const Vec3& rhs) const {
	return Vec3(x / rhs.x, y / rhs.y, z / rhs.z);
}

Vec3& Vec3::operator+=(const Vec3& rhs) {
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}
Vec3& Vec3::operator-=(const Vec3& rhs) {
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}
Vec3& Vec3::operator*=(const Vec3& rhs) {
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
	return *this;
}
Vec3& Vec3::operator/=(const Vec3& rhs) {
	x /= rhs.x;
	y /= rhs.y;
	z /= rhs.z;
	return *this;
}

Vec3 Vec3::operator+(const float& s) const {
	return Vec3(x + s, y + s, z + s);
}
Vec3 Vec3::operator-(const float& s) const {
	return Vec3(x - s, y - s, z - s);
}
Vec3 Vec3::operator*(const float& s) const {
	return Vec3(x * s, y * s, z * s);
}
Vec3 Vec3::operator/(const float& s) const {
	return Vec3(x / s, y / s, z / s);
}

Vec3& Vec3::operator+=(const float& s) {
	x += s;
	y += s;
	z += s;
	return *this;
}
Vec3& Vec3::operator-=(const float& s) {
	x -= s;
	y -= s;
	z -= s;
	return *this;
}
Vec3& Vec3::operator*=(const float& s) {
	x *= s;
	y *= s;
	z *= s;
	return *this;
}
Vec3& Vec3::operator/=(const float& s) {
	x /= s;
	y /= s;
	z /= s;
	return *this;
}
