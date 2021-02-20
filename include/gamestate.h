/*
 * Rick van Vonderen
 * 0945444
 * TI2B
 */

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <chrono> // time
#include <thread> // sleep_for

#include "entity.h"
#include "window.h"

class GameState : public Entity {
public:
	static void sleep(int amount) {
		// Sleep for amount ms
		std::this_thread::sleep_for(std::chrono::milliseconds(amount));
	}
};

class GameStateManager {
public:
	GameStateManager() : m_state(nullptr) {
	}

	~GameStateManager() {
		if(m_state != nullptr) {
			m_state->destroy();
			delete m_state;
		}
	}

	void setState(GameState* state) {
		if(m_state != nullptr) {
			m_state->destroy();
			delete m_state;
		}

		m_state = state;
		if(m_state != nullptr) {
			m_state->initialize();
		}
	}

	void update() {
		if(m_state != nullptr) {
			m_state->update();
		}
	}

	void render() {
		if(m_state != nullptr) {
			m_state->render();
		}
	}

private:
	GameState *m_state;
};

extern GameStateManager *g_gameStateManager;

#endif // GAMESTATE_H
