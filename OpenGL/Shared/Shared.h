#pragma once

// gl
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// std
#include <string>

namespace shrd
{
	bool initialize_basic_window(int width, int height, GLFWwindow** out_window);

	std::string read_file_into_string(const std::string& filename);

	bool check_compilation_success(unsigned int shader_id);

	bool try_load_shader(const std::string& file_name, unsigned int* out_shader_id, GLenum shader_type);

	bool check_linking_success(unsigned int program_id);
}