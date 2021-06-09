#include "../include/shader.h"

#include<cerrno>
#include<cstring>
#include<fstream>
#include<iostream>
#include<vector>

std::string readFile(const char* fileName) {
	std::ifstream in(fileName, std::ios::binary);
	if (in) {
		std::string content;
		in.seekg(0, std::ios::end);
		content.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&content[0], content.size());
		in.close();
		return content;
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) {
	const std::string vertexCode   = readFile(vertexFile);
	const char*       vertexSrc    = vertexCode.c_str();

	const std::string fragmentCode = readFile(fragmentFile);
	const char*       fragmentSrc  = fragmentCode.c_str();

	ID = glCreateProgram();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSrc, NULL);
	glCompileShader(vertexShader);
	CompilerError(vertexShader, "VERTEX");

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSrc, NULL);
	glCompileShader(fragmentShader);
	CompilerError(fragmentShader, "FRAGMENT");

	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	glLinkProgram(ID);
	CompilerError(ID, "PROGRAM");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader() { glDeleteProgram(ID); }

void Shader::Use() { glUseProgram(ID); }

void Shader::CompilerError(GLuint shader, const char* type) {

	if (std::strcmp(type, "PROGRAM") != 0) {
		GLint compiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

		if (compiled == GL_FALSE) {
			GLint len;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

			std::vector<GLchar> log(len);
			glGetShaderInfoLog(shader, len, &len, &log[0]);
					
			std::cout << "Shader " << ID << " "
					  << " Compilation Error for: " << type
					  << "\n";

			for (auto& c: log) std::cout << c;
			std::cout << "\n";
		}
	}

	else {
		GLint linked;
		glGetProgramiv(shader, GL_COMPILE_STATUS, &linked);

		if (linked == GL_FALSE) {
			GLint len;
			glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &len);

			std::vector<GLchar> log(len);
			glGetProgramInfoLog(shader, len, &len, &log[0]);
					
			std::cout << "Shader " << ID << " "
					  << "Link Error for: " << type
					  << "\n";

			for (auto& c: log) std::cout << c;
			std::cout << "\n";
		}
	}
}
