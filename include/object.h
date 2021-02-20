/*
 * Rick van Vonderen
 * 0945444
 * TI2B
 */

#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>

#include "entity.h"

class Object : public Entity {
public:
	Object();

// -----------------------------------------

	virtual void initialize();
	virtual void update();
	virtual void render();
	virtual void destroy();

// -----------------------------------------

	glm::vec3 position() const;
	void setPosition(glm::vec3 position);
	void setPosition(float x, float y, float z);
	glm::vec3 rotation() const;
	void setRotation(glm::vec3 rotation);
	void setRotation(float x, float y, float z);
	glm::vec3 scale() const;
	void setScale(glm::vec3 scale);
	void setScale(float x, float y, float z);
	glm::mat4 model() const;
	void setModel(glm::mat4 transform);

private:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	glm::mat4 m_model;
};

#endif // OBJECT_H
