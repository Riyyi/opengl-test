// #include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp> // glm::translate, glm::rotate, glm::scale

#include "object.h"

Object::Object() : Entity(), m_position(), m_rotation(), m_scale(), m_model()
{
	// printf("obj: %s\n", glm::to_string(position()).c_str());
}

// -----------------------------------------

void Object::initialize()
{
}

void Object::update()
{
	// Local space -> World space: model matrix
	m_model = glm::mat4(1.0f);
	// Translate
	m_model = glm::translate(m_model, position());
	// Rotate
	m_model = glm::rotate(m_model, glm::radians(rotation().x),
	                          glm::vec3(1.0, 0.0, 0.0));
	m_model = glm::rotate(m_model, glm::radians(rotation().y),
	                          glm::vec3(0.0, 1.0, 0.0));
	m_model = glm::rotate(m_model, glm::radians(rotation().z),
	                          glm::vec3(0.0, 0.0, 1.0));
	// Scale
	m_model = glm::scale(m_model, scale());
}

void Object::render()
{
}

void Object::destroy()
{
}

// -----------------------------------------

glm::vec3 Object::position() const
{
	return m_position;
}

void Object::setPosition(glm::vec3 position)
{
	m_position = position;
}

void Object::setPosition(float x, float y, float z)
{
	m_position = glm::vec3(x, y, z);
}

glm::vec3 Object::rotation() const
{
	return m_rotation;
}

void Object::setRotation(glm::vec3 rotation)
{
	m_rotation = rotation;
}

void Object::setRotation(float x, float y, float z)
{
	m_rotation = glm::vec3(x, y, z);
}

glm::vec3 Object::scale() const
{
	return m_scale;
}

void Object::setScale(glm::vec3 scale)
{
	m_scale = scale;
}

void Object::setScale(float x, float y, float z)
{
	m_scale = glm::vec3(x, y, z);
}

glm::mat4 Object::model() const {
	return m_model;
}

void Object::setModel(glm::mat4 model) {
	m_model = model;
}
