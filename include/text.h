/*
 * Rick van Vonderen
 * 0945444
 * TI2B
 */

#ifndef TEXT_H
#define TEXT_H

#include <iostream>

#include <glm/glm.hpp>

#include "object.h"

class Shader;

class Text : public Object {
public:
	Text();
	~Text();

// -----------------------------------------

	void initialize();
	void update();
	void render();
	void destroy();

// -----------------------------------------

	void setText(std::string text);

private:
	unsigned int m_vao;
	unsigned int m_vbo;
	glm::vec3 m_color;
	Shader *m_shader;
	std::string m_text;
};

#endif // TEXT_H
