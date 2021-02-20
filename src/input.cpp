#include <cstring> // memset, memcpy

#include "input.h"
#include "window.h"

InputManager::InputManager()
{
	initialize();
}

InputManager::~InputManager()
{
	destroy();
}

// -----------------------------------------

void InputManager::initialize()
{
	// Set every key to release state
	memset(&m_previousKeyStates, GLFW_RELEASE, sizeof(char) * GLFW_KEY_LAST);
	memset(&m_currentKeyStates, GLFW_RELEASE, sizeof(char) * GLFW_KEY_LAST);

	m_firstMouse = true;
	// Set cursor in middle of the screen initially
	m_xLast = g_window->width() / 2;
	m_yLast = g_window->height() / 2;
}

void InputManager::update()
{
}

void InputManager::render()
{
	// Copy current key states to previous
	memcpy(&m_previousKeyStates, &m_currentKeyStates, sizeof(char) * GLFW_KEY_LAST);

	// Stop mouse movement
	m_xOffset = 0.0f;
	m_yOffset = 0.0f;
}

void InputManager::destroy()
{
}

// -----------------------------------------

char InputManager::keyState(int key)
{
	if (m_previousKeyStates[key] == GLFW_RELEASE &&
	    m_currentKeyStates[key] == GLFW_RELEASE) {
		return InputManager::UP;
	}
	if (m_previousKeyStates[key] == GLFW_RELEASE &&
	    m_currentKeyStates[key] == GLFW_PRESS) {
		return InputManager::PRESSED;
	}
	if (m_previousKeyStates[key] == GLFW_PRESS &&
	    m_currentKeyStates[key] == GLFW_PRESS) {
		return InputManager::DOWN;
	}
	if (m_currentKeyStates[key] == GLFW_REPEAT) {
		return InputManager::DOWN;
	}
	if (m_previousKeyStates[key] == GLFW_PRESS &&
	    m_currentKeyStates[key] == GLFW_RELEASE) {
		return InputManager::RELEASED;
	}

	return InputManager::UP;
}

void InputManager::setKeyState(int key, int scancode, int action, int mode)
{
	if (key != GLFW_KEY_UNKNOWN) {
		m_currentKeyStates[key] = (char)action;
	}

	// Suppress unused warning
	(void)scancode;
	(void)mode;
}

float InputManager::xOffset()
{
	return m_xOffset;
}

float InputManager::yOffset()
{
	return m_yOffset;
}

void InputManager::setMouse(double xpos, double ypos)
{
	// Prevent weird jump on first cursor window enter
	if(m_firstMouse) {
        m_xLast = xpos;
        m_yLast = ypos;
        m_firstMouse = false;
    }

	m_xOffset = xpos - m_xLast;
	// Reversed since y-coordinates range from bottom to top
	m_yOffset = m_yLast - ypos;
	m_xLast = xpos;
	m_yLast = ypos;
}

// @Todo
// - Instead of copying the entire key array into the previous array each frame.
//   Have a pointer point to one of the arrays.
//   To read input, say: array that pointer points to now = current,
//                       array that pointer does not point to now = previous.
//   At the end of the frame, point the pointer to the other array.
//   (?) How to get not point to array now easily? maybe two pointers that swap
//       - current pointer
//       - previous pointer
