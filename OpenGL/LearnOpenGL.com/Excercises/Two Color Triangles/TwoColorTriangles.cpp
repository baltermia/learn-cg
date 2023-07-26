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

		// vbo
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

	// First
	glUseProgram(m_gl_program_id);

	glBindVertexArray(m_vao1);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// Second
	glUseProgram(m_gl_program_id_2);

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

	glDeleteProgram(m_gl_program_id_2);

	return true;
}

bool TwoColorTriangles::tmpl_load_shaders()
{
	bool success;

	// First load vertex shader (used for both programs)
	Shader vertex_shader;
	success = Shader::from_file("both.vert", GL_VERTEX_SHADER, &vertex_shader);

	// Load Fragment Shader program1
	{
		Shader fragment_shader_1;
		success = Shader::from_file("black.frag", GL_FRAGMENT_SHADER, &fragment_shader_1);

		// Load Shader into Program

		vertex_shader.attach_to_program(m_gl_program_id);
		fragment_shader_1.attach_to_program(m_gl_program_id);
		glLinkProgram(m_gl_program_id);

		success = shrd::check_linking_success(m_gl_program_id);

		fragment_shader_1.clean();
	}

	// Load Fragment Shader program2
	{
		Shader fragment_shader_2;
		success = Shader::from_file("white.frag", GL_FRAGMENT_SHADER, &fragment_shader_2);

		// Load Shader into Program

		vertex_shader.attach_to_program(m_gl_program_id_2);
		fragment_shader_2.attach_to_program(m_gl_program_id_2);
		glLinkProgram(m_gl_program_id_2);

		success = shrd::check_linking_success(m_gl_program_id_2);

		fragment_shader_2.clean();
	}

	vertex_shader.clean();

	return true;
}
