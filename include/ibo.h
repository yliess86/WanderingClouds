#ifndef IBO_H
#define IBO_H

#include "../vendor/include/glad/glad.h"

class IBO {
public:
	GLuint ID;

	IBO (const GLuint* indices, GLsizeiptr size);
	~IBO();

	void Bind  ();
	void Unbind();
};

#endif
