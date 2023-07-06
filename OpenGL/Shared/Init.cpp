// Shared.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"

#include "Init.h"

// shared
#include "IO.h"

// std
#include <iostream>

namespace shrd
{

	bool initialize_basic_window(const std::pair<int, int>& window_size, 
								 const std::string& window_name, 
								 const std::pair<int, int>& opengl_version,
								 GLFWwindow** out_window)
	{
		/* --------------------------------- */
		/* Initialize GLFW */

		// initialize glfw
		glfwInit();

		// set OpenGL version
		// check installed version with a tool such as https://realtech-vr.com/home/glview
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, opengl_version.first);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, opengl_version.second);

		// explicitly use core version (so no major backwards-compatibility)
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// set property specific on macos systems (note that opengl 4.6 doesnt work on macos, so make sure to downgrade it above)
#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

		/* --------------------------------- */
		/* Create Window Object */

		* out_window = glfwCreateWindow(window_size.first, window_size.second, window_name.c_str(), NULL, NULL);

		if (out_window == NULL)
		{
			std::cout << "Failed to create GLFW Window object" << std::endl;
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(*out_window);

		/* --------------------------------- */
		/* Initialize GLAD */
		// this is strictly neccessary before using any OpenGL function

		// glfwGetProcAddress defis the correct function pointers based on which OS the code is compiling for
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return false;
		}

		/* --------------------------------- */
		/* Configure OpenGL */

		// offset (0,0)
		glViewport(0, 0, window_size.first, window_size.second);

		return true;
	}

	bool check_compilation_success(GLuint shader_id)
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

	bool try_load_shader(const std::string& file_name, GLuint* out_shader_id, GLenum shader_type)
	{
		*out_shader_id = glCreateShader(shader_type);

		std::string shader_source = read_file_into_string(file_name);
		const char* source_ptr = shader_source.c_str();

		glShaderSource(*out_shader_id, 1, &source_ptr, NULL);
		glCompileShader(*out_shader_id);

		return check_compilation_success(*out_shader_id);
	}

	bool check_linking_success(GLuint program_id)
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
