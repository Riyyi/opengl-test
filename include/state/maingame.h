/*
 * Rick van Vonderen
 * 0945444
 * TI2B
 */

#ifndef MAINGAME_H
#define MAINGAME_H

#define CUBE 6
#define CUBE_SIZE 15

#include <array>

#include "gamestate.h"

class Object;
class Text;

class MainGame : public GameState
{
public:
    void initialize();
    void update();
    void render();
    void destroy();

private:
	std::array<Object *, CUBE_SIZE> m_object;
	Text *m_text;
};

#endif // MAINGAME_H
