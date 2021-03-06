#include "texture.h"

#include <GL/glew.h>
#include "stb_image/stb_image.h"

Texture::Texture(const std::string& path, bool generateMipMaps)
	:m_rendererID(0), m_filepath(path), m_localBuffer(nullptr), m_width(0), m_height(0), m_bpp(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_localBuffer = stbi_load(path.c_str(), &m_width, &m_height, &m_bpp, STBI_rgb_alpha);
	glGenTextures(1, &m_rendererID);

	//glEnable(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_rendererID);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	for (int i = 0; i < 6; ++i) {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer);
	}

	if (generateMipMaps)
		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0); //unbind texture

	if (m_localBuffer)
		stbi_image_free(m_localBuffer);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_rendererID);
}

void Texture::bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_rendererID);
}

void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}