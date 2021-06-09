#include "../include/quad.h"

#include <iostream>

Quad::Quad(const Shader* shader): shader(shader) {
	vao = new VAO();
	vao->Bind();
	
	vbo = new VBO(QUAD_VERTICES, sizeof(QUAD_VERTICES));
	ibo = new IBO(QUAD_INDICES,  sizeof(QUAD_INDICES) );

	vao->LinkAttrib(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), nullptr);
	vao->LinkAttrib(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	vao->Unbind();
	vbo->Unbind();
	ibo->Unbind();
}

Quad::~Quad() {
	shader = nullptr;
	
	delete vao;
	delete vbo;
	delete ibo;

	vao = nullptr;
	vbo = nullptr;
	ibo = nullptr;
}

void Quad::Draw() {
	vao->Bind();
	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
