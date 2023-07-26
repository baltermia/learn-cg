#pragma once

// gl
#include "glad/glad.h"

// std
#include <string_view>

class Shader
{
// Construction
public:
	static bool from_file(std::string_view filename, GLuint shader_type, Shader* out_shader);
	static bool from_source(std::string_view source, GLuint shader_type, Shader* out_shader);

	Shader();

// Functions
public:
	void attach_to_program(GLuint program_id);
	void clean();

// Properties
public:
	GLuint prop_shader_id() const { return m_shader_id; }
	GLuint prop_shader_type() const { return m_shader_type; }

private:
	Shader(std::string_view source, GLuint shader_type);

	GLuint m_shader_id = -1;
	GLuint m_shader_type = -1;
};
