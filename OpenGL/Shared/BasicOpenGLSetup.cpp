#include "pch.h"
#include "framework.h"

#include "BasicOpenGLSetup.h"

// shared
#include "IO.h"
#include "Init.h"

constexpr const char* c_default_vertex_shader_filename = "shader.vert";
constexpr const char* c_default_fragment_shader_filename = "shader.frag";

constexpr const char* c_default_shader_vertex = "#version 460 core\n"
    "layout (location = 0) in vec3 pos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(pos, 1.0);\n"
	"}\0";

constexpr const char* c_default_shader_fragment = "#version 460 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\n\0";

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
			// toggle between polygon and normal mode
			if (glfwGetKey(m_window, GLFW_KEY_1) == GLFW_PRESS)
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			if (glfwGetKey(m_window, GLFW_KEY_2) == GLFW_PRESS)
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

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

	if (!tmpl_clear_resources())
		return false;

	glfwTerminate();
	
	return true;
}

bool shrd::BasicOpenGLSetup::tmpl_frame_input()
{
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_window, true);

	return true;
}

bool shrd::BasicOpenGLSetup::tmpl_load_shaders()
{
	/* ------------------------------------- */
	// Load Vertex Shader
	GLuint vertex_shader;

	std::string vertex_source =
		shrd::file_exists(c_default_vertex_shader_filename) ?
			read_file_into_string(c_default_vertex_shader_filename) :
			c_default_shader_vertex;

	if (!shrd::try_load_shader(vertex_source, &vertex_shader, GL_VERTEX_SHADER))
		return false;

	/* ------------------------------------- */
	// Load Fragment Shader
	GLuint fragment_shader;

	std::string fragment_source =
		shrd::file_exists(c_default_fragment_shader_filename) ?
			read_file_into_string(c_default_fragment_shader_filename) :
			c_default_shader_fragment;

	if (!shrd::try_load_shader(fragment_source, &fragment_shader, GL_FRAGMENT_SHADER))
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
