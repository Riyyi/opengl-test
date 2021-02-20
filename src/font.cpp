#include <glad/glad.h>

#include "font.h"
#include "texture.h"

FT_Face FontManager::loadFont(const std::string &path)
{
	// Return previously loaded font
	auto iter = m_fontList.find(path);
	if (iter != m_fontList.end()) {
		return m_fontList[path];
	}

	// Init FreeType library
	FT_Library ft;
	if (FT_Init_FreeType(&ft)) {
		printf("FontManager::loadFont::ERROR::FREETYPE: Could not init FreeType Library\n");
	}

	// Load font
	FT_Face face;
	if (FT_New_Face(ft, path.c_str(), 0, &face)) {
		printf("FontManager::loadFont::FAILED\n%s\n", path.c_str());
	}
	else {
		// Define font size for this face
		FT_Set_Pixel_Sizes(face, 0, 24); // face, width, height, where width = dynamic

		// Create character list of the first 128 ascii characters
		for (unsigned char c = 0; c < 128; c++) {

			// Creat 8-bit bitmap image of the character
			if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
				printf("FontManager::loadFont::ERROR::FREETYTPE: Failed to load Glyph\n");
				continue;
			}

			// Create texture
			unsigned int texture = g_textureManager->createTexture(
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				face->glyph->bitmap.buffer,
				GL_CLAMP_TO_EDGE,
				GL_LINEAR,
				GL_LINEAR
				);

			// Create character
			Character character = {
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				face->glyph->advance.x
			};

			// Construct and insert new element in the map
			m_characterList.emplace(c, character);
		}

		// Construct and insert new element in the unordered_map
		m_fontList.emplace(path, face);
	}

	// Clean resources
	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	return face;
}

// -----------------------------------------

Character FontManager::character(const char character) const
{
	return m_characterList.at(character);
}

const std::map<const char, Character> &FontManager::characterList() const
{
	return m_characterList;
}

// @Todo link fontList to characterList via:
// <freetype/freetype.h>
// typedef struct FT_FaceRec_*  FT_Face;
