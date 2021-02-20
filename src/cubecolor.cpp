#include <cmath> // sin, fmod
#include <cstdio> // printf

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtx/transform.hpp> // glm::translate, glm::rotate, glm::scale

#include "camera.h"
#include "cubecolor.h"
#include "shader.h"
#include "window.h"

CubeColor::CubeColor() : Object(), m_lineMode(false), m_color(1.0f), m_shader(nullptr)
{
	initialize();
}

CubeColor::CubeColor(float r, float g, float b, bool lineMode)
{
	setColor(r, g, b);
	setLineMode(lineMode);
	initialize();
}

CubeColor::~CubeColor()
{
	destroy();
}

// -----------------------------------------

void CubeColor::initialize()
{
	printf("CubeColor::initialize\n");

	setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	setScale(glm::vec3(1.0f, 1.0f, 1.0f));

	// Vertex attribute pointer size
	int p1Size = 3;
	int p2Size = 3;
	// Vertex data
	float vertexData[] = {
		//  x      y      z      r     g     b
		// Front
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		// Back
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		// Right
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
		// Left
		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
		// Bottom
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		// To
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
	};
	m_vSize = sizeof(vertexData) / sizeof(vertexData[0]) / (p1Size + p2Size);
	m_shader = g_window->shaderColor();

	// If color besides glm::vec3(1.0f) has been set, overwrite rainbow pattern
	if (m_color != glm::vec3(1.0f)) {
		// Loop through all 'rows'
		for (unsigned int i = p1Size; i < m_vSize * (p1Size + p2Size); i += p1Size + p2Size) {
			vertexData[i]     = m_color.r;
			vertexData[i + 1] = m_color.g;
			vertexData[i + 2] = m_color.b;
		}
	}

	// Create objects
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    // Bind vertex array object
	glBindVertexArray(m_vao);

	// Bind vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	int stride = (p1Size + p2Size) * sizeof(float);
	//~ Set vertex shader attribute pointers
	unsigned int p1 = glGetAttribLocation(m_shader->program(), "aPos");
	glEnableVertexAttribArray(p1);
	// Specify vertex data interpretation
	glVertexAttribPointer(
		p1,        // Index
		p1Size,    // Size
		GL_FLOAT,  // Data type
		GL_FALSE,  // Normalize
		stride,    // Stride, byte offset between vertex attributes
		(void*)0); // Pointer, byte offset

	unsigned int p2 = glGetAttribLocation(m_shader->program(), "aColor");
	glEnableVertexAttribArray(p2);
	// Specify vertex data interpretation
	glVertexAttribPointer(
		p2,
		p2Size,
		GL_FLOAT,
		GL_FALSE,
		stride,
		(void*)(p1Size * sizeof(float)));
	//~

	// Unbind vertex array object
	glBindVertexArray(0);
}

void CubeColor::update()
{
	float timeValue = glfwGetTime();
	float loopValue = (std::sin(timeValue) / 2.0f) + 0.5f;
	if (m_color == glm::vec3(1.0f)) {
		setPosition(position().x, position().y, -loopValue * 6 + 6);
	}
	else if (m_lineMode) {
		setScale(loopValue, loopValue, loopValue);
	}

	// Call parent update
	Object::update();
}

void CubeColor::render()
{
	// Enable wireframe mode
	if (m_lineMode) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	// Render
	m_shader->use();
	m_shader->setFloat("model", model());
	m_shader->setFloat("view", g_window->camera()->model());
	m_shader->setFloat("projection", g_window->camera()->projection());

	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, m_vSize);
	glBindVertexArray(0);

	// Disable wireframe mode
	if (m_lineMode) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void CubeColor::destroy()
{
	// Clean resources
	glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
}

// -----------------------------------------

void CubeColor::setLineMode(bool lineMode)
{
	m_lineMode = lineMode;
}

void CubeColor::setColor(float r, float g, float b)
{
	m_color = glm::vec3(r, g, b);
}
