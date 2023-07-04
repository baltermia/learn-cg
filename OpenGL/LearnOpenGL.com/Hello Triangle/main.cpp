// gl
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// std
#include <iostream>

// lib
#include "..\..\Shared\Shared.h"

void callback_framebuffer_size_changed(GLFWwindow* window, int width, int height);

void frame_process_input(GLFWwindow* window);
void frame_render(unsigned int program_id, unsigned int vertex_array_object);

void create_triangle(unsigned int program_id);

int main()
{
	int width = 800;
	int height = 600;

	/* --------------------------------- */
	/* Initialize GLFW */

	// initialize glfw
	glfwInit();

	// set OpenGL version
	// check installed version with a tool such as https://realtech-vr.com/home/glview
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	// explicitly use core version (so no major backwards-compatibility)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// set property specific on macos systems (note that opengl 4.6 doesnt work on macos, so make sure to downgrade it above)
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	/* --------------------------------- */
	/* Create Window Object */

	GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL.com - Hello Triangle", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW Window object" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	/* --------------------------------- */
	/* Initialize GLAD */
	// this is strictly neccessary before using any OpenGL function

	// glfwGetProcAddress defis the correct function pointers based on which OS the code is compiling for
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	/* --------------------------------- */
	/* Configure OpenGL */

	// offset (0,0)
	glViewport(0, 0, width, height);

	// create callback which changes the gl-viewport automatically when the glfw-window gets resized
	glfwSetFramebufferSizeCallback(window, callback_framebuffer_size_changed);

	/* --------------------------------- */
	/* Create Triangle */

	unsigned int gl_program = glCreateProgram();

	// vao
	unsigned int vertex_array_object;
	glGenVertexArrays(1, &vertex_array_object);

	glBindVertexArray(vertex_array_object);

	create_triangle(gl_program);

	glBindVertexArray(0);

	/* --------------------------------- */
	/* Render-Loop */

	while (!glfwWindowShouldClose(window))
	{
		frame_process_input(window);

		frame_render(gl_program, vertex_array_object);

		// double buffer
		glfwSwapBuffers(window);

		// checks for events
		glfwPollEvents();
	}

	/* --------------------------------- */
	/* Clean Up / Deallocate */

	glfwTerminate();

	/* --------------------------------- */

}

/* Callbacks */

void callback_framebuffer_size_changed(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

/* ------------------------------------- */
/* Functions that get called for each frame */

void frame_process_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void frame_render(unsigned int program_id, unsigned int vertex_array_object)
{
	// color that gets replaced with
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	// clear all colors
	glClear(GL_COLOR_BUFFER_BIT);

	// use vao
	glUseProgram(program_id);
	glBindVertexArray(vertex_array_object);

	// draw
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}

/* ------------------------------------- */

void create_triangle(unsigned int program_id)
{
	/* ------------------------------------- */
	// Write Memory to GPU
	float vertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	// vbo
	unsigned int vertex_buffer_object;
	glGenBuffers(1, &vertex_buffer_object);

	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/* ------------------------------------- */
	// Load Vertex Shader
	bool success;

	unsigned int vertex_shader;
	success = shrd::try_load_shader("triangle.vert", &vertex_shader, GL_VERTEX_SHADER);

	/* ------------------------------------- */
	// Load Fragment Shader
	unsigned int fragmet_shader;
	success = shrd::try_load_shader("triangle.frag", &fragmet_shader, GL_FRAGMENT_SHADER);

	/* ------------------------------------- */
	// Load Shaders into Program

	glAttachShader(program_id, vertex_shader);
	glAttachShader(program_id, fragmet_shader);
	glLinkProgram(program_id);

	success = shrd::check_linking_success(program_id);

	// Delete shadeers after linking
	glDeleteShader(vertex_shader);
	glDeleteShader(fragmet_shader);

	/* ------------------------------------- */
	// Vertex-Linking Attributes

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)NULL);
	glEnableVertexAttribArray(0);

	/* ------------------------------------- */
}