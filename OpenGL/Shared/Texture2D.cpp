#include "pch.h"
#include "framework.h"

#include "Texture2D.h"

// std
#include <vector>
#include <iostream>

// vcpkg
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture2D::Texture2D(std::string_view filepath, GLuint unit)
	: m_filepath(filepath),
	  m_unit(unit)
{
	// otherwise, the image is flipped upside down (since GL has 0,0 in bottom instead of top)
	stbi_set_flip_vertically_on_load(true);

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

	// if image conatins alpha-channel (meaning RGB + 1 extra), then use GL_RGBA format
	GLenum format = GL_RGB + (m_channels == 4);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, m_data.data());
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(m_data.data());
}

void Texture2D::bind()
{
	glActiveTexture(GL_TEXTURE0 + m_unit);
	glBindTexture(GL_TEXTURE_2D, m_texture_id);
}

void Texture2D::attach_uniform(GLuint program_id, std::string_view var_name)
{
	glUseProgram(program_id);
	glUniform1i(glGetUniformLocation(program_id, var_name.data()), m_unit);
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
