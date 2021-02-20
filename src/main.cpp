/*
 * Rick van Vonderen
 * 0945444
 * TI2B
 *
 * https://www.glfw.org/docs/latest/build_guide.html#build_link_cmake_source
 *
 * `m_` for member variables,
 * `s_` for static variables,
 * `g_` for global variables.
 */

#include <cstdio> // printf

#include "font.h"
#include "gamestate.h"
#include "input.h"
#include "state/maingame.h"
#include "texture.h"
#include "window.h"

// Define globals here
GameStateManager *g_gameStateManager;
InputManager *g_inputManager;
TextureManager *g_textureManager;
FontManager *g_fontManager;
Window *g_window;

#include <glm/gtx/transform.hpp> // glm::translate, glm::rotate, glm::scale

int main(int argc, char *argv[])
{

#ifndef NDEBUG
	printf("--- Debug mode ---\n");

	// Supress unused warning
	(void)argc;
	(void)argv;
#endif

	printf("--- Main ---\n");

	g_window = new Window(1280, 720);
	g_inputManager = new InputManager();
	g_textureManager = new TextureManager();
	g_fontManager = new FontManager();
	g_gameStateManager = new GameStateManager();
	g_gameStateManager->setState(new MainGame());

	g_fontManager->loadFont("../data/font/DejaVuSansMono.ttf");

    // Window loop
	while (!g_window->shouldClose()) {
		g_window->update();
		g_inputManager->update();
		g_gameStateManager->update();
		g_gameStateManager->render();
		g_inputManager->render();
		g_window->render();
	}

	delete g_gameStateManager;
	delete g_fontManager;
	delete g_textureManager;
	delete g_inputManager;
	delete g_window;

	return 0;
}
