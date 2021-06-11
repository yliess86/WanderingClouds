#include "../include/navigator.h"

void Nav::UpdateDir() {
	Controller& controller = Controller::Instance();

	dir = Vec3(0, 0, 0);
	if (controller.isPressed(Controls::UP   )) dir.y -= 1;
	if (controller.isPressed(Controls::DOWN )) dir.y += 1;
	if (controller.isPressed(Controls::RIGHT)) dir.x -= 1;
	if (controller.isPressed(Controls::LEFT )) dir.x += 1;

	float mag = dir.Mag();
	if (mag > 0) dir /= mag;
}

void Nav::Update(const float& dt) {
	UpdateDir();

 	transform.acc  = dir * ACCELERATION;
	transform.vel += (transform.acc - Vec3(1, 1, 0) * transform.vel * FRICTION) * dt;
	transform.pos += transform.vel * dt;
}
