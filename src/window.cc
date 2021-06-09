#include "../include/window.h"

Window::Window(
	const char*         title,
	const unsigned int* size,
	const unsigned int* opengl_version,
	const float*        clear_color
): title(title), size(size), opengl_version(opengl_version), clear_color(clear_color) {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, opengl_version[0]);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, opengl_version[1]);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(size[0], size[1], title, NULL, NULL);
	if (m_window == NULL) {
		std::cout << "Failed to create GLFW Window\n";
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(m_window);

	gladLoadGL();
	glViewport(0, 0, size[0], size[1]);

	Clear();
	glfwSwapBuffers(m_window);
}

Window::~Window() {
	glfwDestroyWindow(m_window);
	glfwTerminate();

	m_window       = nullptr;
	clear_color    = nullptr;
	title          = nullptr;
	size           = nullptr;
	opengl_version = nullptr;
}

bool Window::Running() { return !glfwWindowShouldClose(m_window); }

void Window::Clear  () {
	glClearColor(clear_color[0], clear_color[1], clear_color[2], clear_color[3]);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::Update() {
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}
