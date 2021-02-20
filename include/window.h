/*
 * Rick van Vonderen
 * 0945444
 * TI2B
 */

#ifndef WINDOW_H
#define WINDOW_H

#include "entity.h"

class Camera;
class GLFWwindow;
class Shader;

class Window : public Entity {
public:
	// Window();
	Window(int width, int height);
	~Window();

	bool shouldClose();

// -----------------------------------------

	void initialize();
	void update();
	void render();
	void destroy();

// -----------------------------------------

	int width();
	int height();
	float aspect();
	float currentTime();
	float deltaTime();

	GLFWwindow *window();
	Shader *shader();
	Shader *shaderColor();
	Shader *shaderFont();
	Camera *camera();

// -----------------------------------------

	static void errorCallback(int error, const char *description);
	static void keyCallback(GLFWwindow *window, int key, int scancode,
			int action, int mode);
	static void mouseCallback(GLFWwindow* window, double xpos, double ypos);

private:
	int m_width;
	int m_height;
	float m_aspect;
	float m_currentTime;
	float m_lastFrameTime;
	float m_deltaTime;

	GLFWwindow *m_window;
	Shader *m_shader;
	Shader *m_shaderColor;
	Shader *m_shaderFont;
	Camera *m_camera;
};

extern Window *g_window;

#endif // WINDOW_H
