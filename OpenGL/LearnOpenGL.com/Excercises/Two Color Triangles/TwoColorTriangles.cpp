#include "TwoColorTriangles.h"

// std
#include <vector>

bool TwoColorTriangles::tmpl_setup()
{
	{
		// first

		// vao
		glGenVertexArrays(1, &m_vao1);

		glBindVertexArray(m_vao1);
		/* ------------------------------------- */
		// Write Memory to GPU
		std::vector<vec3f> vertices1 =
		{
			{ -0.75f, -0.25f },
			{ -0.25f, -0.25f },
			{ -0.5f,  0.5f }
		};

		// vbo
		glGenBuffers(1, &m_vbo1);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo1);
		glBufferData(GL_ARRAY_BUFFER, vertices1.size() * sizeof(vec3f), vertices1.data(), GL_STATIC_DRAW);

		/* ------------------------------------- */
		// Vertex-Linking Attributes

		glVertexAttribPointer(0, sizeof(vec3f) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(vec3f), (void*)NULL);
		glEnableVertexAttribArray(0);
	}

	{
		// second

		glGenVertexArrays(1, &m_vao2);

		glBindVertexArray(m_vao2);

		std::vector<vec3f> vertices2 =
		{
			{ 0.5f, 0.5f },
			{ 0.25f, -0.25f },
			{ 0.75f,  -0.25f }
		};

		glGenBuffers(1, &m_vbo2);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo2);
		glBufferData(GL_ARRAY_BUFFER, vertices2.size() * sizeof(vec3f), vertices2.data(), GL_STATIC_DRAW);


		glVertexAttribPointer(0, sizeof(vec3f) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(vec3f), (void*)NULL);
		glEnableVertexAttribArray(0);
	}
	
	// unbind
	glBindVertexArray(0);

	return true;
}

bool TwoColorTriangles::tmpl_frame_render()
{
	// color that gets replaced with
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	// clear all colors
	glClear(GL_COLOR_BUFFER_BIT);

	// use vao
	glUseProgram(m_gl_program_id);

	glBindVertexArray(m_vao1);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(m_vao2);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	
	glBindVertexArray(0);

	return true;
}

bool TwoColorTriangles::tmpl_clear_resources()
{
	glDeleteBuffers(1, &m_vbo1);
	glDeleteBuffers(1, &m_vbo2);

	glDeleteVertexArrays(1, &m_vao1);
	glDeleteVertexArrays(1, &m_vao2);

	return true;
}

bool TwoColorTriangles::tmpl_load_shaders()
{


	return true;
}
