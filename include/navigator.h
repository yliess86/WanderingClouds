#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include "./controller.h"
#include "./vec.h"

struct Transform {
	Vec3 pos, vel, acc;
};

class Nav {
public:
	const float ACCELERATION = 2.0;
	const float FRICTION     = 1.0;
	
	Transform transform;
	Vec3      dir;

	Nav(const Vec3& pos, const Vec3& vel, const Vec3& acc):
		transform(Transform{pos, vel, acc}) {}

	void UpdateDir();
	void UpdateAcc();
	
	void Update(const float& dt);
};

#endif
