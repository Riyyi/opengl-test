#include "entity.h"

Entity::Entity() : m_active(true)
{
}

Entity::~Entity()
{
}

// -----------------------------------------

bool Entity::active() const
{
	return m_active;
}

void Entity::setActive(bool active)
{
	m_active = active;
}
