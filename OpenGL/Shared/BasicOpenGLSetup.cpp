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
	glfwTerminate();

	return tmpl_clear_resources();
}
