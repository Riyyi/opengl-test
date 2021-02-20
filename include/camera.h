/*
 * Rick van Vonderen
 * 0945444
 * TI2B
 */

#ifndef CAMERA_H
#define CAMERA_H

#define SPEED 2.5f
#define SENSITIVITY 0.25f
#define NEAR_PlANE 0.1f
#define FAR_PlANE 100.0f

#include "object.h"

class Camera : public Object {
public:
	void initialize();
	void update();
	void render();
	void destroy();

// -----------------------------------------

	float fov();
	void setFov(float fov);
	glm::mat4 projection();

private:
	float m_fov;
	float m_pitch;
	float m_yaw;
	glm::vec3 m_up;
	glm::mat4 m_projection;
};

#endif // CAMERA_H
