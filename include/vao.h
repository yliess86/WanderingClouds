#ifndef VAO_H
#define VAO_H

#include "../vendor/include/glad/glad.h"
#include "./vbo.h"

class VAO {
public:
	GLuint ID;

	VAO ();
	~VAO();

	void LinkAttrib(
		VBO*       vbo,
		GLuint     layout,
		GLuint     numComponents,
		GLenum     type,
		GLsizeiptr stride,
		void*      offset
	);

	void Bind  ();	
	void Unbind();	
};

#endif
