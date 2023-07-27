#pragma once

// std
#include <string_view>
#include <span>

// gl
#include "glad/glad.h"

class Texture2D
{
// Construction
public:
	Texture2D(std::string_view filepath);

// Functions
public:
	Texture2D& load_into_gl();
	void clean();
	
	Texture2D& bind_id(GLuint* out_texture_id);

// Properties
public:
	GLuint prop_texture_id() const { return m_texture_id; }
	int prop_width() const { return m_width; }
	int prop_height() const { return m_height; }
	int prop_channels() const { return m_channels; }

	std::span<unsigned char> prop_data() const { return m_data; }

	std::string_view prop_filepath() const { return m_filepath; }

private:
	static void set_gl_texture_parameters();

private:
	std::string_view m_filepath;
	GLuint m_texture_id = 0;
	int m_width = 0;
	int m_height = 0;
	int m_channels = 0;
	std::span<unsigned char> m_data;
};
