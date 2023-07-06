#include "pch.h"
#include "framework.h"

#include "BasicOpenGLSetup.h"

// shared
#include "Init.h"

void shrd::BasicOpenGLSetup::callback_framebuffer_size_changed(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

shrd::BasicOpenGLSetup::BasicOpenGLSetup(int width, int height)
{
	m_window_size = { width, height };
}

bool shrd::BasicOpenGLSetup::initialize()
{
	if (!shrd::initialize_basic_window(prop_window_size(), prop_window_name(), tmpl_prop_opengl_version(), &m_window))
		return false;

	glfwSetFramebufferSizeCallback(m_window, callback_framebuffer_size_changed);

	m_gl_program_id = glCreateProgram();

	if (!tmpl_load_shaders())
		return false;

	return tmpl_setup();
}

bool shrd::BasicOpenGLSetup::run()
{
	try
	{
		while (!glfwWindowShouldClose(m_window))
		{
			if (!tmpl_frame_input() ||
				!tmpl_frame_render())
				return false;

			// double buffer
			glfwSwapBuffers(m_window);

			// checks for events
			glfwPollEvents();
		}

		return true;
	}
	catch (...)
	{
		return false;
	}
}

bool shrd::BasicOpenGLSetup::clean()
{
	glDeleteProgram(m_gl_program_id);

	glfwTerminate();

	return tmpl_clear_resources();
}

inline bool shrd::BasicOpenGLSetup::tmpl_frame_input()
{
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_window, true);

	return true;
}

bool shrd::BasicOpenGLSetup::tmpl_load_shaders()
{
	/* ------------------------------------- */
	// Load Vertex Shader
	unsigned int vertex_shader;
	if (!shrd::try_load_shader("shader.vert", &vertex_shader, GL_VERTEX_SHADER))
		return false;

	/* ------------------------------------- */
	// Load Fragment Shader
	unsigned int fragment_shader;
	if (!shrd::try_load_shader("shader.frag", &fragment_shader, GL_FRAGMENT_SHADER))
		return false;

	/* ------------------------------------- */
	// Load Shaders into Program

	glAttachShader(m_gl_program_id, vertex_shader);
	glAttachShader(m_gl_program_id, fragment_shader);
	glLinkProgram(m_gl_program_id);

	if (!shrd::check_linking_success(m_gl_program_id))
		return false;

	// Delete shadeers after linking
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return true;
}
