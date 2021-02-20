#include <cstdio> // printf

#include <glm/glm.hpp>

#include "cube.h"
#include "cubecolor.h"
#include "state/maingame.h"
#include "text.h"

void MainGame::initialize() {
	printf("MainGame::initialize\n");

	glm::vec3 cubeColors[CUBE_SIZE] = {
		// Textured cube
		glm::vec3( 0.6f,  0.2f,  0.2f),
		glm::vec3( 0.2f,  0.6f,  0.2f),
		glm::vec3( 0.2f,  0.2f,  0.6f),
		glm::vec3( 1.0f,  1.0f,  1.0f),
		glm::vec3( 1.0f,  1.0f,  1.0f),
		glm::vec3( 1.0f,  1.0f,  1.0f),
		// Colored cube
		glm::vec3( 0.6f,  0.2f,  0.2f),
		glm::vec3( 0.2f,  0.6f,  0.2f),
		glm::vec3( 0.2f,  0.2f,  0.6f),
		glm::vec3( 0.6f,  0.2f,  0.2f),
		glm::vec3( 0.2f,  0.6f,  0.2f),
		glm::vec3( 0.2f,  0.2f,  0.6f),
		glm::vec3( 1.0f,  1.0f,  1.0f),
		glm::vec3( 1.0f,  1.0f,  1.0f),
		glm::vec3( 1.0f,  1.0f,  1.0f),
	};

	glm::vec3 cubePositions[CUBE_SIZE] = {
		// Textured cube
		glm::vec3( 0.0f,  0.0f,  0.0f),
		glm::vec3( 2.0f,  0.0f,  0.0f),
		glm::vec3( 4.0f,  0.0f,  0.0f),
		glm::vec3( 0.0f,  2.0f,  0.0f),
		glm::vec3( 2.0f,  2.0f,  0.0f),
		glm::vec3( 4.0f,  2.0f,  0.0f),
		// Colored cube
		glm::vec3( 0.0f,  0.0f,  6.0f),
		glm::vec3( 2.0f,  0.0f,  6.0f),
		glm::vec3( 4.0f,  0.0f,  6.0f),
		glm::vec3( 0.0f,  2.0f,  6.0f),
		glm::vec3( 2.0f,  2.0f,  6.0f),
		glm::vec3( 4.0f,  2.0f,  6.0f),
		glm::vec3( 0.0f,  4.0f,  6.0f),
		glm::vec3( 2.0f,  4.0f,  6.0f),
		glm::vec3( 4.0f,  4.0f,  6.0f),
	};

	bool cubeLine[CUBE_SIZE] = {
		// Colored cube
		false,
		false,
		false,
		true,
		true,
		true,
		true,
	};

	for(int i = 0; i < CUBE; i++) {
		m_object[i] = new Cube(cubeColors[i].x, cubeColors[i].y, cubeColors[i].z);
		m_object[i]->setPosition(cubePositions[i]);
	}
	for(int i = CUBE; i < CUBE_SIZE; i++) {
		m_object[i] = new CubeColor(cubeColors[i].x, cubeColors[i].y, cubeColors[i].z,
		                            cubeLine[i - CUBE]);
		m_object[i]->setPosition(cubePositions[i]);
	}

	m_text = new Text();
	m_text->setText("Test");
}

void MainGame::update() {
	for(int i = 0; i < CUBE_SIZE; i++) {
		m_object[i]->update();
	}

	m_text->update();
}

void MainGame::render() {
	for(int i = 0; i < CUBE_SIZE; i++) {
		m_object[i]->render();
	}

	m_text->render();
}

void MainGame::destroy() {
	for(int i = 0; i < CUBE_SIZE; i++) {
		m_object[i]->destroy();
	}

	m_text->destroy();
}
