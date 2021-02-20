/*
 * Rick van Vonderen
 * 0945444
 * TI2B
 */

#ifndef CUBE_H
#define CUBE_H

#include <glm/glm.hpp>

#include "object.h"

class Shader;

class Cube : public Object {
public:
	Cube();
	Cube(float r, float g, float b);
	~Cube();

// -----------------------------------------

	void initialize();
	void update();
	void render();
	void destroy();

// -----------------------------------------

	void setColor(float r, float g, float b);

private:
	unsigned int m_vao;
	unsigned int m_vbo;
	unsigned int m_vSize;
	unsigned int m_texture;
	glm::vec3 m_color;
	Shader *m_shader;
};

#endif // CUBE_H
