#ifndef UNIFORM_H
#define UNIFORM_H

#include "../vendor/include/glad/glad.h"

class Uniform {
public:
	GLuint ID;

	Uniform(GLuint ID): ID(ID) {}
	~Uniform() = default;
};

class Uniform1i: public Uniform {
public:
	Uniform1i(GLuint ID): Uniform(ID) {}

	void SetValue(int value);
};

class Uniform1f: public Uniform {
public:
	Uniform1f(GLuint ID): Uniform(ID) {}

	void SetValue(float value);
};

class Uniform2f: public Uniform {
public:
	Uniform2f(GLuint ID): Uniform(ID) {}

	void SetValue(float* value);
};

class Uniform3f: public Uniform {
public:
	Uniform3f(GLuint ID): Uniform(ID) {}

	void SetValue(float* value);
};

#endif
