#include "TwoTriangles.h"

bool TwoTriangles::tmpl_setup()
{
	// vao
	glGenVertexArrays(1, &m_vao);

	glBindVertexArray(m_vao);
	/* ------------------------------------- */
	// Write Memory to GPU
	float vertices[] =
	{
		-0.75f, -0.75f, 0.0f,
		0.75f, -0.0f, 0.0f,
		0.0f,  0.75f, 0.0f
	};

	// vbo
	glGenBuffers(1, &m_vbo);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/* ------------------------------------- */
	// Vertex-Linking Attributes

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)NULL);
	glEnableVertexAttribArray(0);

	/* ------------------------------------- */

	// unbind
	glBindVertexArray(0);

	return true;
}

bool TwoTriangles::tmpl_frame_render()
{
	// color that gets replaced with
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	// clear all colors
	glClear(GL_COLOR_BUFFER_BIT);

	// use vao
	glUseProgram(m_gl_program_id);
	glBindVertexArray(m_vao);

	// draw
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);

	return true;
}

bool TwoTriangles::tmpl_clear_resources()
{
	glDeleteBuffers(1, &m_vbo);

	glDeleteVertexArrays(1, &m_vao);

	return true;
}
