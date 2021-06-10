#include "../include/controller.h"

Controller& Controller::Instance() {
	static Controller instance;
	return instance;
}

bool Controller::isPressed(const Controls& control) {
	return m_inputs[control].current;
}

Controller::Controller() {
	m_inputs[Controls::UP   ] = ControlState{ false, false };
	m_inputs[Controls::LEFT ] = ControlState{ false, false };
	m_inputs[Controls::DOWN ] = ControlState{ false, false };
	m_inputs[Controls::RIGHT] = ControlState{ false, false };
}

void Controller::Handle(
	[[maybe_unused]]GLFWwindow* window,
					int key,
	[[maybe_unused]]int scancode,
					int action,
	[[maybe_unused]]int mods
) {
	Controller& controller = Controller::Instance();

	switch (key) {
	case Controls::UP:
		controller.setInput(Controls::UP,    action != GLFW_RELEASE);
		break;
	case Controls::LEFT:
		controller.setInput(Controls::LEFT,  action != GLFW_RELEASE);
		break;
	case Controls::DOWN:
		controller.setInput(Controls::DOWN,  action != GLFW_RELEASE);
		break;
	case Controls::RIGHT:
		controller.setInput(Controls::RIGHT, action != GLFW_RELEASE);
		break;
	}
}

void Controller::setInput(const Controls& controls, const bool& value) {
	m_inputs[controls].previous = m_inputs[controls].current;
	m_inputs[controls].current  = value;
}
