#include "../include/navigator.h"

void Nav::Update(const float& dt) {
	Controller& controller = Controller::Instance();

	Vec3 dir = Vec3(0, 0, 0.1);
	if (controller.isPressed(Controls::UP   )) dir.y -= 1;
	if (controller.isPressed(Controls::DOWN )) dir.y += 1;
	if (controller.isPressed(Controls::RIGHT)) dir.x -= 1;
	if (controller.isPressed(Controls::LEFT )) dir.x += 1;

	float mag = dir.Mag();
	if (mag > 0) dir /= mag;

	transform.acc  = dir * 0.1;
	transform.vel += transform.acc * dt;
	transform.pos += transform.vel * dt;
}
