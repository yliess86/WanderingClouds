#ifndef WINDOW_H
#define WINDOW_H

#include "../vendor/include/glad/glad.h"

#include<iostream>
#include<GLFW/glfw3.h>

class Window {
public:
	const char*         title;
	const unsigned int* size;
	const unsigned int* opengl_version;
	const float*        clear_color;

	Window(
		const char*         title,
		const unsigned int* size,
		const unsigned int* opengl_version,
		const float*        clear_color
	);

	~Window();

	bool Running();

	void Clear ();
	void Update();
	
protected:
	GLFWwindow* m_window;
};

#endif
