#ifndef SHADER_H
#define SHADER_H

#include "../vendor/include/glad/glad.h"

#include<string>
#include<unordered_map>

#include "../include/uniform.h"

std::string readFile(const char* fileName);

class Shader {
public:
	GLuint                                    ID;
	std::unordered_map<std::string, Uniform*> uniforms;

	Shader (const char* vertexFile, const char* fragmentFile);
	~Shader();

	void Use();

	template<typename UniformType>
	UniformType* GetUniform(std::string name);

private:
	void CompilerError(GLuint shader, const char* type);
};

template<typename UniformType>
UniformType* Shader::GetUniform(std::string name) {
	if (uniforms.find(name) == uniforms.end()) {
		GLuint u_ID = glGetUniformLocation(ID, name.c_str());
		uniforms[name] = new UniformType(u_ID);
	}

	return (UniformType*)uniforms[name];
}

#endif
