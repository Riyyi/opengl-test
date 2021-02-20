#include <climits> // UINT_MAX

#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "texture.h"

unsigned int TextureManager::loadTexture(const std::string &path)
{
	// Return previously loaded texture
	auto iter = m_textureList.find(path);
	if (iter != m_textureList.end()) {
		return m_textureList[path];
	}

	int width;
	int height;
	int channels;
	// Load image data
	stbi_set_flip_vertically_on_load(true);
	unsigned char *image = stbi_load(path.c_str(), &width, &height, &channels, STBI_default);

	unsigned int texture = UINT_MAX;
	if (!image) {
		printf("TextureManager::loadTexure::FAILED\n%s\n", path.c_str());
	}
	else {
		int format = 0;
		if (channels == 3) {
			format = GL_RGB;
		}
		else if (channels == 4) {
			format = GL_RGBA;
		}

		// Generate texture
		texture = createTexture(
			format,
			width,
			height,
			image,
			GL_REPEAT,
			GL_NEAREST,
			GL_NEAREST,
			true);

		// Construct and insert new element in the unordered_map
		m_textureList.emplace(path, texture);
	}

	// Clean resources
	stbi_image_free(image);

	return texture;
}

void TextureManager::deleteTexture(const unsigned int texture)
{
	glDeleteTextures(1, &texture);
}

unsigned int TextureManager::createTexture(
	int format, unsigned int width, unsigned int height, const void *image,
	int wrap, int filterMin, int filterMag, bool genMipmap)
{
	unsigned int texture = UINT_MAX;

	// Create texture object
	glGenTextures(1, &texture);

	// Bind texture object
	glBindTexture(GL_TEXTURE_2D, texture);

	// Set unpacking of pixel data to byte-alignment,
	// this prevents alignment issues when using a single byte for color
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Generate texture
	glTexImage2D(
		GL_TEXTURE_2D,    // Texture target
		0,                // Midmap level, base starts at level 0
		format,           // Texture format
		width, height,    // Image width/height
		0,                // Always 0 (legacy)
		format,           // Texture source format
		GL_UNSIGNED_BYTE, // Texture source datatype
		image);           // Image data

	// Set the texture wrapping / filtering options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap); // X
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap); // Y
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin); // Minify
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMag); // Magnify

	if (genMipmap) {
		// Automatically generate all mipmap levels
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	// Unbind texture object
	glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}
