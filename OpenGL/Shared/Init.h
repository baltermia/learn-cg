#pragma once

// gl
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// std
#include <string>

namespace shrd
{
	bool initialize_basic_window(const std::pair<int, int>& window_size, 
								 const std::string& window_name, 
								 const std::pair<int, int>& opengl_version,
								 GLFWwindow** out_window);

	bool check_compilation_success(GLuint shader_id);

	bool try_load_shader(const std::string& file_name, GLuint* out_shader_id, GLenum shader_type);

	bool check_linking_success(GLuint program_id);
}
