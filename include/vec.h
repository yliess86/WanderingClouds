#ifndef VEC_H
#define VEC_H

#include<cmath>

struct Vec3 {
	float x, y, z;

	Vec3(): Vec3(0, 0, 0) {}
	Vec3(float x, float y, float z): x(x), y(y), z(z) {}

	float* Data();

	float Mag();

	Vec3 operator+(const Vec3& rhs) const;
	Vec3 operator-(const Vec3& rhs) const;
	Vec3 operator*(const Vec3& rhs) const;
	Vec3 operator/(const Vec3& rhs) const;

	Vec3& operator+=(const Vec3& rhs);
	Vec3& operator-=(const Vec3& rhs);
	Vec3& operator*=(const Vec3& rhs);
	Vec3& operator/=(const Vec3& rhs);

	Vec3 operator+(const float& s) const;
	Vec3 operator-(const float& s) const;
	Vec3 operator*(const float& s) const;
	Vec3 operator/(const float& s) const;

	Vec3& operator+=(const float& s);
	Vec3& operator-=(const float& s);
	Vec3& operator*=(const float& s);
	Vec3& operator/=(const float& s);
};

#endif
