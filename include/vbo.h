#ifndef VBO_H
#define VBO_H

#include "../vendor/include/glad/glad.h"

class VBO {
public:
	GLuint ID;

	VBO (const GLfloat* vertices, GLsizeiptr size);
	~VBO();

	void Bind  ();
	void Unbind();
};

#endif
