#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include "./controller.h"
#include "./vec.h"

struct Transform {
	Vec3 pos, vel, acc;
};

class Nav {
public:
	Transform transform;

	Nav(const Vec3& pos):
		transform(Transform{pos, Vec3(), Vec3()}) {}

	void Update(const float& dt);
};

#endif
