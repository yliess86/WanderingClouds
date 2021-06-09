#ifndef TEXTURE_H
#define TEXTURE_H

#include "../vendor/include/glad/glad.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include "../vendor/include/stb/stb_image.h"
#pragma GCC diagnostic pop

#include "./shader.h"

float* readTex3D(const char* path, int* width, int* height, int* depth);


class Tex {
public:
	GLuint ID;
	GLenum slot;
	GLenum textureType;

	Tex (GLenum slot, GLenum textureType);
	~Tex();
	
	void Bind  ();
	void Unbind();
};

class Tex2D: public Tex {
public:
	Tex2D (
		const char* path,
		GLenum slot,
		GLenum format,
		GLenum type
	);
	~Tex2D() {}
};

class Tex3D: public Tex {
public:
	Tex3D (
		const char* path,
		GLenum slot,
		GLenum format,
		GLenum type
	);
	~Tex3D() {}
};

#endif
