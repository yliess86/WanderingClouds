#ifndef QUAD_H
#define QUAD_H

#include "../vendor/include/glad/glad.h"

#include "./shader.h"
#include "./vao.h"
#include "./vbo.h"
#include "./ibo.h"

const GLfloat QUAD_VERTICES[] = {
	-1.0f, -1.0f, 0.0f,   0.0f, 0.0f,
	 1.0f, -1.0f, 0.0f,   1.0f, 0.0f,
	-1.0f,  1.0f, 0.0f,   0.0f, 1.0f,
	 1.0f,  1.0f, 0.0f,   1.0f, 1.0f
//    x      y     z       u     v
};

const GLuint  QUAD_INDICES [] = {
	0, 1, 2,  // #0
	1, 2, 3   // #1
};

class Quad {
public:
	const Shader* shader;
	
	VAO* vao;
	VBO* vbo;
	IBO* ibo;

	Quad(const Shader* shader);
	~Quad();

	void Draw  ();
};

#endif
