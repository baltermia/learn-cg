#pragma once

// gl
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// std
#include <string>

namespace shrd
{
	bool initialize_basic_window(int width, int height, const std::string& window_name, GLFWwindow** out_window);

	bool check_compilation_success(unsigned int shader_id);

	bool try_load_shader(const std::string& file_name, unsigned int* out_shader_id, GLenum shader_type);

	bool check_linking_success(unsigned int program_id);
}
