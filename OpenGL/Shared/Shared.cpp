// Shared.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"

#include "Shared.h"

// std
#include <iostream>
#include <fstream>

namespace shrd
{

	std::string read_file_into_string(const std::string& filename)
	{
		std::ifstream file(filename);

		std::string content{ std::istreambuf_iterator<char>(file),
							  std::istreambuf_iterator<char>() };

		file.close();

		return content;
	}

	bool check_compilation_success(unsigned int shader_id)
	{
		int  success;
		char infoLog[512];
		glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(shader_id, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		return success;
	}


	bool try_load_shader(const std::string& file_name, unsigned int* out_shader_id, GLenum shader_type)
	{
		*out_shader_id = glCreateShader(shader_type);

		std::string shader_source = read_file_into_string(file_name);
		const char* source_ptr = shader_source.c_str();

		glShaderSource(*out_shader_id, 1, &source_ptr, NULL);
		glCompileShader(*out_shader_id);

		return check_compilation_success(*out_shader_id);
	}

	bool check_linking_success(unsigned int program_id)
	{
		int  success;
		char infoLog[512];
		glGetProgramiv(program_id, GL_LINK_STATUS, &success);

		if (!success)
		{
			glGetProgramInfoLog(program_id, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}

		return success;
	}

}
