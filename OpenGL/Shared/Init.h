#pragma once

// gl
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// std
#include <string_view>
#include <utility>

namespace shrd
{
	bool initialize_basic_window(const std::pair<int, int>& window_size, 
								 std::string_view window_name, 
								 const std::pair<int, int>& opengl_version,
								 GLFWwindow** out_window);

	bool check_compilation_success(GLuint shader_id);

	bool try_load_shader(std::string_view source, GLuint* out_shader_id, GLenum shader_type);

	bool try_load_shader_from_file(std::string_view path, GLuint* out_shader_id, GLenum shader_type);
	
	bool check_linking_success(GLuint program_id);
}
