#include <cstdio>  // printf

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stb_image.h>

#include "camera.h"
#include "input.h"
#include "shader.h"
#include "window.h"

// Window::Window() : Entity(), m_width(0), m_height(0)
// {
// }

Window::Window(int width, int height) : Entity(), m_width(width), m_height(height)
{
	this->initialize();
}

Window::~Window()
{
	this->destroy();
}

bool Window::shouldClose()
{
	return glfwWindowShouldClose(m_window);
}

// -----------------------------------------

void Window::initialize()
{
	// Error callback function
	glfwSetErrorCallback(Window::errorCallback);

	// Init GLFW and set the required options
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that can be used for GLFW's functions
	m_window = glfwCreateWindow(m_width, m_height,
			"Lines", NULL, NULL);
	glfwMakeContextCurrent(m_window);
	if (m_window == NULL) {
		printf("Failed to create GLFW window\n");
		glfwTerminate();
	}

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to initialize OpenGL context\n");
	}

	// Associate the wrapper to the window
	glfwSetWindowUserPointer(m_window, this);

	// Keyboard callback function
	glfwSetKeyCallback(m_window, Window::keyCallback);

	// Capture cursor and hide it
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Mouse callback function
	glfwSetCursorPosCallback(m_window, Window::mouseCallback);

	// Load shaders
	m_shader = new Shader("../data/glsl/simple.vert", "../data/glsl/simple.frag");
	m_shaderColor = new Shader("../data/glsl/color.vert", "../data/glsl/color.frag");
	m_shaderFont = new Shader("../data/glsl/font.vert", "../data/glsl/font.frag");

	// Enable z-buffer / depth buffer
	glEnable(GL_DEPTH_TEST);

	m_lastFrameTime = 0.0f;
	m_deltaTime = 0.0f;

	// Initialize camera
	m_camera = new Camera();
	m_camera->initialize();
}

void Window::update()
{
	// Clear buffers
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Check if any events have been activated (keypresses, mouse movement)
	glfwPollEvents();

	// Reset the viewport to the new window size
	glfwGetFramebufferSize(m_window, &m_width, &m_height);
	m_aspect = (float)m_width / (float)m_height;
	glViewport(0, 0, m_width, m_height);

	// Calculate delta time
	m_currentTime = glfwGetTime();
	m_deltaTime = m_currentTime - m_lastFrameTime;
	m_lastFrameTime = m_currentTime;

	m_camera->update();
}

void Window::render()
{
	m_camera->render();

	// Swap the screen buffers
	glfwSwapBuffers(m_window);
}

void Window::destroy()
{
	delete m_shader;
	delete m_shaderColor;
	delete m_shaderFont;
	delete m_camera;

	// Clean GLFW allocated resources
	glfwDestroyWindow(m_window);
	glfwTerminate();
	printf("Cleaned up GLFW resources..\n");
}

// -----------------------------------------

int Window::width()
{
	return m_width;
}

int Window::height()
{
	return m_height;
}

float Window::aspect()
{
	return m_aspect;
}

float Window::currentTime()
{
	return m_currentTime;
}

float Window::deltaTime()
{
	return m_deltaTime;
}

GLFWwindow *Window::window()
{
	return m_window;
}

Shader *Window::shader()
{
	return m_shader;
}

Shader *Window::shaderColor()
{
	return m_shaderColor;
}

Shader *Window::shaderFont()
{
	return m_shaderFont;
}

Camera *Window::camera()
{
	return m_camera;
}

// -----------------------------------------

void Window::errorCallback(int error, const char* description)
{
	fputs(description, stderr);

	// Suppress unused warning
	(void)error;
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode,
		int action, int mode)
{
	// printf("%d\n", key);

	// Quit game
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	// Mouse capture
	if (key == GLFW_KEY_LEFT_SUPER && action == GLFW_PRESS)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	else
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	g_inputManager->setKeyState(key, scancode, action, mode);
}

void Window::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	g_inputManager->setMouse(xpos, ypos);

	// Suppress unused warning
	(void)window;
}
