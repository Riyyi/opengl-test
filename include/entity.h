/*
 * Rick van Vonderen
 * 0945444
 * TI2B
 */

#ifndef ENTITY_H
#define ENTITY_H

class Entity {
public:
	Entity();
	virtual ~Entity();

// -----------------------------------------

	virtual void initialize() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void destroy() = 0;

// -----------------------------------------

	bool active() const;
	void setActive(bool active);

private:
	bool m_active;
};

#endif // ENTITY_H
