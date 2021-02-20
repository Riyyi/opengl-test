#include <glm/gtx/transform.hpp> // glm::lookAt, glm::perspective
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective

#include "camera.h"
#include "input.h"
#include "window.h"

void Camera::initialize()
{
	setPosition(glm::vec3(0.0f, 0.0f, 3.0f));
	setRotation(glm::vec3(0.0f, 0.0f, -1.0f));
	setScale(glm::vec3(1.0f, 1.0f, 1.0f));
	setFov(90.0f);
	m_pitch = 0.0f;
	m_yaw = 0.0f;
	// Up vector in world space
	m_up = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::update()
{
	// Get mouse movement offset compared to last frame
	float xoffset = g_inputManager->xOffset() * SENSITIVITY;
	float yoffset = g_inputManager->yOffset() * SENSITIVITY;
	m_yaw   += xoffset;
	m_pitch += yoffset;
	// Prevent gimbal lock
	if(m_pitch > 89.0f)  m_pitch =  89.0f;
	if(m_pitch < -89.0f) m_pitch = -89.0f;

	// Update camera rotation, by calculating direction vector via yaw and pitch
	setRotation(
		cos(glm::radians(m_pitch)) * cos(glm::radians(m_yaw)),
		sin(glm::radians(m_pitch)),
		cos(glm::radians(m_pitch)) * sin(glm::radians(m_yaw)));
	setRotation(glm::normalize(rotation()));
	// The direction vector is based on
	// Camera direction (z): normalize(position - target)
	// Right axis       (x): normalize(cross(up, direction))
	// Up axis          (y): cross(direction, right)

	// Source: https://learnopengl.com/img/getting-started/camera_axes.png

	// Cross = combination of two vectors in 3D space,
	//         where result is always perpendicular to both of the vectors

	// Update camera position
	float cameraSpeed = SPEED * g_window->deltaTime();
	// WASD movement
	if (g_inputManager->keyState(GLFW_KEY_W) == InputManager::DOWN) {
		setPosition(position() + cameraSpeed * rotation());
	}
	if (g_inputManager->keyState(GLFW_KEY_S) == InputManager::DOWN) {
		setPosition(position() - cameraSpeed * rotation());
	}
	if (g_inputManager->keyState(GLFW_KEY_A) == InputManager::DOWN) {
		setPosition(position() -
		            glm::normalize(glm::cross(rotation(), m_up)) * cameraSpeed);
	}
	if (g_inputManager->keyState(GLFW_KEY_D) == InputManager::DOWN) {
		setPosition(position() +
		            glm::normalize(glm::cross(rotation(), m_up)) * cameraSpeed);
	}
	// Up / down movement
	if (g_inputManager->keyState(GLFW_KEY_SPACE) == InputManager::DOWN) {
		setPosition(position().x, position().y + cameraSpeed, position().z);
	}
	if (g_inputManager->keyState(GLFW_KEY_LEFT_SHIFT) == InputManager::DOWN) {
		setPosition(position().x, position().y - cameraSpeed, position().z);
	}

	// Update camera matrix

	// Local space -> World space: model matrix
	// Is done in Object::update()

	// World space -> View space: view matrix
	setModel(glm::lookAt(position(), position() + rotation(), m_up));

	// View space -> Clip space: projection matrix
	m_projection = glm::perspective(glm::radians(m_fov), g_window->aspect(),
	                                NEAR_PlANE, FAR_PlANE);

	// Clip space -> Screen space: viewport transform
	// Is done in the fragment shader using the settings of glViewport

	// Souce: https://learnopengl.com/img/getting-started/coordinate_systems.png
}

void Camera::render()
{
}

void Camera::destroy()
{
}

// -----------------------------------------

float Camera::fov() {
	return m_fov;
}

void Camera::setFov(float fov)
{
	m_fov = fov;
}

glm::mat4 Camera::projection() {
	return m_projection;
}
