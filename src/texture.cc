#include "../include/texture.h"

#include <fstream>
#include <iostream>
#include <vector>

float* readTex3D(const char* path, int* width, int* height, int* depth) {
	std::ifstream file(path, std::ifstream::in | std::ifstream::binary);
	
	file.read(reinterpret_cast<char*>(height), sizeof(int));
	file.read(reinterpret_cast<char*>(width ), sizeof(int));
	file.read(reinterpret_cast<char*>(depth ), sizeof(int));
	
	const size_t size  = (*height) * (*width) * (*depth);

	float* data = new float[size];
	for (size_t i = 0; i < size; i++)
		file.read(reinterpret_cast<char*>(&data[i]), sizeof(float));

	bool err = file.eof();
	file.close();
	
	return (err)? nullptr: data;
}

Tex::Tex(GLenum slot, GLenum textureType):
	slot(slot), textureType(textureType) { glGenTextures(1, &ID); }
Tex::~Tex() { glDeleteTextures(1, &ID); }

void Tex::Bind  () {
	glActiveTexture(slot);
	glBindTexture(textureType, ID);
}
void Tex::Unbind() { glBindTexture(textureType, 0); }

Tex2D::Tex2D(
	const char* path,
	GLenum slot,
	GLenum format,
	GLenum type
): Tex(slot, GL_TEXTURE_2D) {
	stbi_set_flip_vertically_on_load(true);	
	Bind();

	glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(textureType, GL_TEXTURE_WRAP_S,     GL_REPEAT );
	glTexParameteri(textureType, GL_TEXTURE_WRAP_T,     GL_REPEAT );

	int W = 0, H = 0, C = 0;
	unsigned char* bytes = stbi_load(path, &W, &H, &C, 0);

	if (bytes)
		glTexImage2D(textureType, 0, format, W, H, 0, format, type, bytes); 
	else {
		std::cout << "Failed to load Texture2D: " << path << "\n";
		exit(EXIT_FAILURE);
	}

	stbi_image_free(bytes);
	Unbind();
}

Tex3D::Tex3D(
	const char* path,
	GLenum slot,
	GLenum format,
	GLenum type
): Tex(slot, GL_TEXTURE_3D) {
	Bind();

	glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(textureType, GL_TEXTURE_WRAP_S,     GL_REPEAT);
	glTexParameteri(textureType, GL_TEXTURE_WRAP_T,     GL_REPEAT);
	glTexParameteri(textureType, GL_TEXTURE_WRAP_R,     GL_REPEAT);

	int W = 0, H = 0, D = 0;
	const float* data = readTex3D(path, &W, &H, &D);

	if (data)
		glTexImage3D(textureType, 0, format, W, H, D, 0, format, type, data);
	else {
		std::cout << "Failed to load Texture3D: " << path << "\n";
		exit(EXIT_FAILURE);
	}

	delete data;
	Unbind();
}
