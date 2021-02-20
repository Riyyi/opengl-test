#include <cmath> // sin, fmod
#include <cstdio> // printf

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtx/transform.hpp> // glm::translate, glm::rotate, glm::scale

#include "camera.h"
#include "cube.h"
#include "shader.h"
#include "texture.h"
#include "window.h"

Cube::Cube() : Object(), m_color(1.0f), m_shader(nullptr)
{
	initialize();
}

Cube::Cube(float r, float g, float b) : Cube()
{
	m_color = glm::vec3(r, g, b);
}

Cube::~Cube()
{
	destroy();
}

// -----------------------------------------

void Cube::initialize()
{
	printf("Cube::initialize\n");

	setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	setScale(glm::vec3(1.0f, 1.0f, 1.0f));

	// Vertex attribute pointer size
	int p1Size = 3;
	int p2Size = 2;
	// Vertex data
	float vertexData[] = {
		//  x      y      z     tx    ty
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	};
	m_vSize = sizeof(vertexData) / sizeof(vertexData[0]) / (p1Size + p2Size);
	m_shader = g_window->shader();

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

	unsigned int p2 = glGetAttribLocation(m_shader->program(), "aTextCoord");
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

	// Texture
	m_texture = g_textureManager->loadTexture("../data/gfx/awesome-face.png");
}

void Cube::update()
{
	float timeValue = glfwGetTime();
	float amount = std::fmod(timeValue * 50, 360);
	setRotation(amount, amount, 0.0f);

	// Call parent update
	Object::update();
}

void Cube::render()
{
	// Render
	m_shader->use();
	m_shader->setFloat("color", glm::vec4(m_color, 1.0f));
	m_shader->setFloat("model", model());
	m_shader->setFloat("view", g_window->camera()->model());
	m_shader->setFloat("projection", g_window->camera()->projection());

	glBindVertexArray(m_vao);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glDrawArrays(GL_TRIANGLES, 0, m_vSize);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Cube::destroy()
{
	// Clean resources
	glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
}

// -----------------------------------------

void Cube::setColor(float r, float g, float b)
{
	m_color = glm::vec3(r, g, b);
}

// @Todo
// + Local postition flipped
// + Shader textures
// + World positions ?
// + Cleanup and understand camera::update
// + Cleanup cube more
// ! Only set shader projection on camera fov update, remove projection getter

// - Object: model matrix (add translate to origin before rotation)
// - Object: model matrix (rotations in radians here or in child (cube)?)
//   |- rotation around 2 axis ?
//    https://learnopengl.com/Getting-started/Coordinate-Systems
// + Object setter overload, take 3 floats as well
// - Object setter, single float position update (?)
// - Cube init: check if glGetAttribLocation != UINT_MAX
// - Text in window: FPS, Player position, player rotation
