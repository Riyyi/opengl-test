#include <climits> // UINT_MAX
#include <cstdio>  // printf
#include <fstream> // ifstream
#include <iostream> // ios
#include <memory> // make_unique

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "shader.h"

Shader::Shader(const std::string &vertexSource, const std::string &fragmentSource) :
	m_program(0)
{
	std::string vertex = readFile(vertexSource);
	std::string fragment = readFile(fragmentSource);

	unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertex.c_str());
	unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragment.c_str());
	if (vertexShader != UINT_MAX && fragmentShader != UINT_MAX) {
		m_program = linkShader(vertexShader, fragmentShader);
	}
}

Shader::~Shader()
{
	if (m_program > 0) {
		glDeleteProgram(m_program);
		m_program = 0;
	}
}

// -----------------------------------------

std::string Shader::readFile(const std::string &path) const
{
	// Create input stream object and open file
	std::ifstream file;
	file.open(path.c_str(), std::ifstream::in);

	// Check if file exists
	if (!file.is_open()) {
		printf("Shader::readFile::FAILED\n%s\n", path.c_str());
		return nullptr;
	}

	// Get length of the file
	file.seekg(0, std::ios::end);
	unsigned int length = file.tellg();
	file.seekg(0, std::ios::beg);

	// Allocate memory filled with zeros
	auto buffer = std::make_unique<char[]>(length + 1);

	file.read(buffer.get(), length);
	file.close();

	// Create string from the buffer
	std::string result = std::string(buffer.get(), length + 1);

	return result;
}

unsigned int Shader::compileShader(unsigned int type, const char *source) const
{
	// Create new shader
	unsigned int shader;
	shader = glCreateShader(type);
	// Attach shader source to shader object
	glShaderSource(shader, 1, &source, nullptr);
	// Compile shader
	glCompileShader(shader);
	// Check compilation status
	if (checkStatus(shader)) {
		return shader;
	}

	// On fail
	glDeleteShader(shader);
	return UINT_MAX;
}

unsigned int Shader::linkShader(unsigned int vertex, unsigned int fragment) const
{
	// Create new shader program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	// Attach both shaders to the shader program
	glAttachShader(shaderProgram, vertex);
	glAttachShader(shaderProgram, fragment);
	// Setup vertex attributes
	glBindAttribLocation(shaderProgram, 0, "aPos");
	// Link the shaders
	glLinkProgram(shaderProgram);
	// Clear resources
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	// Check linking status
	if (checkStatus(shaderProgram, true)) {
		return shaderProgram;
	}

	// On fail
	glDeleteProgram(shaderProgram);
	return UINT_MAX;
}

int Shader::checkStatus(unsigned int check, bool isProgram) const
{
	int  success;
	char infoLog[INFO_LOG_SIZE];

	// Check shader or program
	!isProgram
		? glGetShaderiv(check, GL_COMPILE_STATUS, &success)
		: glGetProgramiv(check, GL_LINK_STATUS, &success);

	if (!success) {
		// Check shader or program
		!isProgram
			? glGetShaderInfoLog(check, INFO_LOG_SIZE, nullptr, infoLog)
			: glGetProgramInfoLog(check, INFO_LOG_SIZE, nullptr, infoLog);
		printf("Shader::checkStatus::FAILED\n%s\n", infoLog);
	}

	return success;
}

void Shader::use() const
{
	glUseProgram(m_program);
}

void Shader::setFloat(const std::string &name, float f1, float f2, float f3, float f4) const
{
	// Set uniform vec4 data
	glUniform4f(glGetUniformLocation(m_program, name.c_str()), f1, f2, f3, f4);
}

void Shader::setFloat(const std::string &name, glm::vec3 v) const {
	// Set uniform vec3 data
	glUniform3f(glGetUniformLocation(m_program, name.c_str()), v.x, v.y, v.z);
}

void Shader::setFloat(const std::string &name, glm::vec4 v) const {
	// Set uniform vec4 data
	glUniform4f(glGetUniformLocation(m_program, name.c_str()), v.x, v.y, v.z, v.w);
	// glUniform4fv(glGetUniformLocation(m_program, name.c_str()), 1, glm::value_ptr(v));
}

void Shader::setFloat(const std::string &name, glm::mat4 m) const {
	// Set uniform mat4 data
	glUniformMatrix4fv(glGetUniformLocation(m_program, name.c_str()),
	                   1, GL_FALSE, glm::value_ptr(m));
}

// -----------------------------------------

unsigned int Shader::program() const
{
	return m_program;
}
