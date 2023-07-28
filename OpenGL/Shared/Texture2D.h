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
	/// <summary>
	/// Default empty constructor. The create instance cannot be used but simply takes up space
	/// </summary>
	Texture2D() {}

	/// <summary>
	/// Reads the texture from a image file
	/// </summary>
	Texture2D(std::string_view filepath, GLuint unit = 0);

// Functions
public:
	/// <summary>
	/// Loads the read image data into the opengl memory buffer. This also automatically clears prop_data()
	/// </summary>
	void load_into_gl();
	
	/// <summary>
	/// Binds the texture. This can be used to edit or use the texture (e.g. in the frame-loop)
	/// </summary>
	void bind();

	void attach_uniform(GLuint shader_id, std::string_view var_name);

	/// <summary>
	/// Delete any memory used from gl. The texture cannot be used after calling this
	/// </summary>
	void clean_gl();

// Properties
public:
	GLuint prop_texture_id() const { return m_texture_id; }
	GLuint prop_unit() const { return m_unit; }
	void set_unit(GLuint unit) { m_unit = unit; }
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
	GLuint m_unit = 0;
	int m_width = 0;
	int m_height = 0;
	int m_channels = 0;
	std::span<unsigned char> m_data;
};
