/*
 * Rick van Vonderen
 * 0945444
 * TI2B
 */

#ifndef FONT_H
#define FONT_H

#include <map> // map
#include <string> // string
#include <unordered_map> // unordered_map

#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/glm.hpp>

struct Character {
    unsigned int texture; // ID
    glm::ivec2   size;    // Width / height
    glm::ivec2   bearing; // Offset from baseline to left/top of glyph
    unsigned int advance; // Offset to advance to next glyph
};

class FontManager {
public:
	FT_Face loadFont(const std::string &path);

// -----------------------------------------

	Character character(const char character) const;
	const std::map<const char, Character> &characterList() const;

private:
	std::unordered_map<std::string, FT_Face> m_fontList;

	std::map<const char, Character> m_characterList;
};

extern FontManager *g_fontManager;

#endif // FONT_H
