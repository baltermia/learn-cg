#include "pch.h"
#include "framework.h"

#include "Shader.h"

// lib
#include "IO.h"

// std
#include <array>
#include <iostream>

bool Shader::from_file(std::string_view filename, GLuint shader_type, Shader* out_shader)
{
	if (shrd::file_exists(filename))
		return Shader::from_source(shrd::read_file_into_string(filename), shader_type, out_shader);

	std::cout << "ERROR:SHADER::FILE_NOT_FOUND\n" << filename << std::endl;
	return false;
}

bool Shader::from_source(std::string_view source, GLuint shader_type, Shader* out_shader)
{
	*out_shader = { source, shader_type };

	GLuint shader_id = out_shader->prop_shader_id();

	glCompileShader(shader_id);

	int success;
	std::array<char, 512> log{};
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader_id, log.size(), NULL, log.data());
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << log.data() << std::endl;
	}

	return success;
}

Shader::Shader()
	: m_shader_id(-1),
	  m_shader_type(-1)
{ }

Shader::Shader(std::string_view source, GLuint shader_type)
	: m_shader_type(shader_type)
{
	m_shader_id = glCreateShader(m_shader_type);

	const char* source_ptr = source.data();

	glShaderSource(m_shader_id, 1, &source_ptr, NULL);
}

void Shader::attach_to_program(GLuint program_id)
{
	glAttachShader(program_id, m_shader_id);
}

void Shader::clean()
{
	glDeleteShader(m_shader_id);
}