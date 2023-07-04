// gl
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// std
#include <iostream>

// lib
#include "..\..\Shared\Shared.h"

void callback_framebuffer_size_changed(GLFWwindow* window, int width, int height);

void frame_process_input(GLFWwindow* window);
void frame_render(unsigned int program_id, unsigned int vertex_array_object, unsigned int element_buffer_object);

void create_square(unsigned int program_id, unsigned int* out_element_buffer_object);

bool run(GLFWwindow* window);
bool clean();

int main()
{
	GLFWwindow* window;
	shrd::initialize_basic_window(800, 600, "Element Buffer Objects", &window);
	run(window);
	clean();
}

bool run(GLFWwindow* window)
{
	// create callback which changes the gl-viewport automatically when the glfw-window gets resized
	glfwSetFramebufferSizeCallback(window, callback_framebuffer_size_changed);

	/* --------------------------------- */
	/* Create square */

	unsigned int gl_program = glCreateProgram();

	// ebo
	unsigned int element_buffer_object;

	// vao
	unsigned int vertex_array_object;
	glGenVertexArrays(1, &vertex_array_object);
	
	glBindVertexArray(vertex_array_object);

	create_square(gl_program, &element_buffer_object);

	glBindVertexArray(0);

	/* --------------------------------- */
	/* Render-Loop */

	while (!glfwWindowShouldClose(window))
	{
		frame_process_input(window);

		frame_render(gl_program, vertex_array_object, element_buffer_object);

		// double buffer
		glfwSwapBuffers(window);

		// checks for events
		glfwPollEvents();
	}

	return true;
}

bool clean()
{
	glfwTerminate();

	return true;
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

void frame_render(unsigned int program_id, unsigned int vertex_array_object, unsigned int element_buffer_object)
{
	// color that gets replaced with
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	// clear all colors
	glClear(GL_COLOR_BUFFER_BIT);

	// use vao
	glUseProgram(program_id);
	glBindVertexArray(vertex_array_object);

	// draw
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


	glBindVertexArray(0);
}

/* ------------------------------------- */

void create_square(unsigned int program_id, unsigned int* out_element_buffer_object)
{
	/* ------------------------------------- */
	// Write Memory to GPU
	float vertices[] = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	// ebo
	glGenBuffers(1, out_element_buffer_object);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *out_element_buffer_object);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// vbo
	unsigned int vertex_buffer_object;
	glGenBuffers(1, &vertex_buffer_object);

	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/* ------------------------------------- */
	// Load Vertex Shader
	bool success;

	unsigned int vertex_shader;
	success = shrd::try_load_shader("square.vert", &vertex_shader, GL_VERTEX_SHADER);

	/* ------------------------------------- */
	// Load Fragment Shader
	unsigned int fragmet_shader;
	success = shrd::try_load_shader("square.frag", &fragmet_shader, GL_FRAGMENT_SHADER);

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