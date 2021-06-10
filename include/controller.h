#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <GLFW/glfw3.h>

#include<map>

enum Controls {
	UP    = GLFW_KEY_W,
	LEFT  = GLFW_KEY_A,
	DOWN  = GLFW_KEY_S,
	RIGHT = GLFW_KEY_D,
};

struct ControlState { bool current, previous; };

class Controller {
public:
	Controller(const Controller&)            = delete;
    Controller(Controller&&)                 = delete;
    Controller& operator=(const Controller&) = delete;
    Controller& operator=(Controller&&)      = delete;

	static Controller& Instance();
	static void Handle(GLFWwindow* window, int key, int scancode, int action, int mods);

	bool isPressed(const Controls& control);

protected:
	std::map<int, ControlState> m_inputs;

	Controller ();
	~Controller() = default;
	
	void setInput(const Controls& controls, const bool& value);
};

#endif
