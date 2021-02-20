/*
 * Rick van Vonderen
 * 0945444
 * TI2B
 */

#ifndef SHADER_H
#define SHADER_H

#define INFO_LOG_SIZE 512

#include <glm/glm.hpp>

#include <string>

class Shader {
public:
	Shader(const std::string &vertexSource, const std::string &fragmentSource);
	~Shader();

// -----------------------------------------

	// Setup shader program
	std::string readFile(const std::string &path) const;
	unsigned int compileShader(unsigned int type, const char *shaderSource) const;
	unsigned int linkShader(unsigned int vertex, unsigned int fragment) const;
	int checkStatus(unsigned int check, bool isProgram = false) const;

	// Use shader program
	void use() const;
	void setFloat(const std::string &name, float f1, float f2, float f3, float f4) const;
	void setFloat(const std::string &name, glm::vec3 v) const;
	void setFloat(const std::string &name, glm::vec4 v) const;
	void setFloat(const std::string &name, glm::mat4 m) const;

// -----------------------------------------

	unsigned int program() const;

private:
	unsigned int m_program;
};

#endif // SHADER_H
