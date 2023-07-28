#include "pch.h"
#include "framework.h"

#include "Texture2D.h"

// std
#include <vector>
#include <iostream>

// vcpkg
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture2D::Texture2D(std::string_view filepath)
	: m_filepath(filepath)
{
	stbi_uc* data = stbi_load(m_filepath.data(), &m_width, &m_height, &m_channels, 0);

	if (data == nullptr)
	{
		std::cout << "ERROR:TEXTURE::COULDNT_LOAD_FILE\n" << m_filepath << std::endl;
		return;
	}

	size_t size = static_cast<size_t>(m_width * m_height * m_channels);

	m_data = { data, size };

	glGenTextures(1, &m_texture_id);
}

void Texture2D::load_into_gl()
{
	glBindTexture(GL_TEXTURE_2D, m_texture_id);

	set_gl_texture_parameters();

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_data.data());
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(m_data.data());
}

void Texture2D::bind()
{
	glBindTexture(GL_TEXTURE_2D, m_texture_id);
}

void Texture2D::clean_gl()
{
	glDeleteTextures(1, &m_texture_id);
}

void Texture2D::set_gl_texture_parameters()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
