/*
 * Rick van Vonderen
 * 0945444
 * TI2B
 */

#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <unordered_map>

class TextureManager {
public:
	unsigned int loadTexture(const std::string &path);
	void deleteTexture(const unsigned int texture);

	unsigned int createTexture(
		int format, unsigned int width, unsigned int height, const void *image,
		int wrap, int filterMin, int filterMag, bool genMipmap = false);

private:
	std::unordered_map<std::string, unsigned int> m_textureList;
};

extern TextureManager *g_textureManager;

#endif // TEXTURE_H
