#include "BasicRaytracing.h"

// std
#include <vector>

// shared
#include "../../Shared/Vec.h"

bool BasicRaytracing::tmpl_setup()
{
	std::vector<Sphere> spheres =
	{
		Sphere
		{
			{ 0, -1, 3 },
			{ 255 },
			1.f
		},
		Sphere
		{
			{ 2, 0, 4 },
			{ 0, 0, 255 },
			1.f
		},
		Sphere
		{
			{ -2, 0, 4 },
			{ 0, 255 },
			1.f
		}
	};

	// vao
	glGenVertexArrays(1, &m_vao);

	glBindVertexArray(m_vao);
	/* ------------------------------------- */
	// Write Memory to GPU
	std::vector<vec3f> vertices =
	{
		// pos			 // col	
		{ -0.5f, -0.5f }, { 1.f },
		{ 0.5f, -0.5f }, { 0.f, 1.f },
		{ 0.0f,  0.5f }, { 0.f, 0.f, 1.f }
	};

	// vbo
	glGenBuffers(1, &m_vbo);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3f), vertices.data(), GL_STATIC_DRAW);

	/* ------------------------------------- */
	// Vertex-Linking Attributes

	glVertexAttribPointer(0, sizeof(vec3f) / sizeof(float), GL_FLOAT, GL_FALSE, 2 * sizeof(vec3f), (void*)NULL);
	glEnableVertexAttribArray(0);

	// this is important for the colors!! :
	glVertexAttribPointer(1, sizeof(vec3f) / sizeof(float), GL_FLOAT, GL_FALSE, 2 * sizeof(vec3f), (void*)sizeof(vec3f)); // last arg is offset
	glEnableVertexAttribArray(1);

	/* ------------------------------------- */

	// unbind
	glBindVertexArray(0);

	return true;
}

bool BasicRaytracing::tmpl_frame_render()
{
	// color that gets replaced with
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	// clear all colors
	glClear(GL_COLOR_BUFFER_BIT);

	// use vao
	glUseProgram(m_gl_program_id);

	// uniforms
	GLuint seconds = glGetUniformLocation(m_gl_program_id, "seconds");
	glUniform1f(seconds, glfwGetTime());

	glBindVertexArray(m_vao);

	// draw
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);

	return true;
}

bool BasicRaytracing::tmpl_clear_resources()
{
	glDeleteBuffers(1, &m_vbo);

	glDeleteVertexArrays(1, &m_vao);

	return true;
}
