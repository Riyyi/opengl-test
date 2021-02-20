/*
 * Rick van Vonderen
 * 0945444
 * TI2B
 */

#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>

#include "entity.h"

class InputManager : public Entity {
public:
	InputManager();
	~InputManager();

// -----------------------------------------

	void initialize();
	void update();
	void render();
	void destroy();

// -----------------------------------------

	enum keyStates {
		UP = 0,
		PRESSED,
		DOWN,
		RELEASED,
	};

	char keyState(int key);
	void setKeyState(int key, int scancode, int action, int mode);
	float xOffset();
	float yOffset();
	void setMouse(double xpos, double ypos);

private:
	char m_previousKeyStates[GLFW_KEY_LAST];
	char m_currentKeyStates[GLFW_KEY_LAST];
	bool m_firstMouse;
	float m_xLast;
	float m_yLast;
	float m_xOffset;
	float m_yOffset;
};

extern InputManager *g_inputManager;

#endif // INPUT_H
