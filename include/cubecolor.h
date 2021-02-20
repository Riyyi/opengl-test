/*
 * Rick van Vonderen
 * 0945444
 * TI2B
 */

#ifndef CUBE_COLOR_H
#define CUBE_COLOR_H

#include <glm/glm.hpp>

#include "object.h"

class Shader;

class CubeColor : public Object {
public:
	CubeColor();
	CubeColor(float r, float g, float b, bool lineMode = false);
	~CubeColor();

// -----------------------------------------

	void initialize();
	void update();
	void render();
	void destroy();

// -----------------------------------------

	void setLineMode(bool lineMode);
	void setColor(float r, float g, float b);

private:
	bool m_lineMode;
	unsigned int m_vao;
	unsigned int m_vbo;
	unsigned int m_vSize;
	glm::vec3 m_color;
	Shader *m_shader;
};

#endif // CUBE_COLOR_H
