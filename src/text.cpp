#include <cstdio> // printf
// #include <iostream>

#include <glad/glad.h>
#include <glm/ext/matrix_clip_space.hpp> // glm::ortho

#include "font.h"
#include "shader.h"
#include "text.h"
#include "texture.h"
#include "window.h"

Text::Text() : Object(), m_color(1.0f), m_shader(nullptr), m_text("")
{
	initialize();
}

Text::~Text()
{
	destroy();
}

// -----------------------------------------

void Text::initialize()
{
	setScale(1.0f, 1.0f, 1.0f);

	m_shader = g_window->shaderFont();

	// Generate buffer
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Text::update()
{
	setPosition(50.0f, 50.0f, 0.0f);
}

void Text::render()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Render
	m_shader->use();
	m_shader->setFloat("color", m_color);
	m_shader->setFloat("projection", glm::ortho(
		                   0.0f, (float)g_window->width(),
		                   0.0f, (float)g_window->height()));

	// glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(m_vao);

	// Iterate through all characters
    std::string::const_iterator c;
    for (c = m_text.begin(); c != m_text.end(); c++)
    {
	    Character ch = g_fontManager->character(*c);
	    // printf("ch:  %u, %d %d, %d %d, %u\n",
	    //        ch.texture, ch.size.x, ch.size.y, ch.bearing.x, ch.bearing.y, ch.advance);

	    float xpos = position().x + ch.bearing.x * scale().x;
	    float ypos = position().y - (ch.size.y - ch.bearing.y) * scale().x;
	    // printf("xpos-ypos:  %f, %f\n", xpos, ypos);

	    float w = ch.size.x * scale().x;
	    float h = ch.size.y * scale().x;
	    // printf("w-h:  %f, %f\n", w, h);

        // Update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0, 0.0 },
            { xpos,     ypos,       0.0, 1.0 },
            { xpos + w, ypos,       1.0, 1.0 },

            { xpos,     ypos + h,   0.0, 0.0 },
            { xpos + w, ypos,       1.0, 1.0 },
            { xpos + w, ypos + h,   1.0, 0.0 }
        };
        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.texture);
        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        // Bitshift by 6 to get value in pixels (2^6 = 64)
        setPosition(position().x + (ch.advance >> 6) * scale().x, position().y, position().z);
    }

	// printf("\n");

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Text::destroy()
{
}

// -----------------------------------------

void Text::setText(std::string text)
{
	m_text = text;
}
