#include "Textures.h"

// shrd
#include "..\..\..\Shared\Vec.h"

// std
#include <vector>

typedef shrd::Vec2<float> vec2f;

struct Vertex
{
	vec3f pos;
	vec2f tex;
	vec3f col;
};

bool Textures::tmpl_setup()
{
	// vao
	glGenVertexArrays(1, &m_vao);

	glBindVertexArray(m_vao);
	/* ------------------------------------- */
	// Write Memory to GPU
	std::vector<Vertex> vertices =
	{
		// pos					// tex
		Vertex{ { .5, .5 },		{ 1, 1 },	{ 1 } },		// tr
		Vertex{ { .5, -.5 },	{ 1, 0 },	{ 0, 1 } },		// br
		Vertex{ { -.5, -.5 },	{ 0, 0 },	{ 0, 0, 1 } },	// bl
		Vertex{ { -.5, .5 },	{ 0, 1 },	{ 1, 1 } }		// tl
	};

	std::vector<vec3ui> indices =
	{
		{ 0, 1, 3 },
		{ 1, 2, 3 }
	};

	// ebo
	glGenBuffers(1, &m_ebo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(vec3ui), indices.data(), GL_STATIC_DRAW);

	// vbo
	glGenBuffers(1, &m_vbo);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	/* ------------------------------------- */
	// Vertex-Linking Attributes

	glVertexAttribPointer(0, sizeof(vec3f) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)NULL);
	glEnableVertexAttribArray(0);

	// this is important for the texture coords!! :
	glVertexAttribPointer(1, sizeof(vec2f) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec3f))); // last arg is offset
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, sizeof(vec3f) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec3f) + sizeof(vec2f)));
	glEnableVertexAttribArray(2);

	// unbind
	glBindVertexArray(0);

	/* ------------------------------------- */
	// Load Textures

	m_texture_wall = { "./Resources/wall.jpg", 0 };
	m_texture_wall.load_into_gl();

	m_texture_face = { "./Resources/face.png", 1 };
	m_texture_face.load_into_gl();

	m_texture_wall.attach_uniform(m_gl_program_id, "texture_wall");
	m_texture_face.attach_uniform(m_gl_program_id, "texture_face");

	return true;
}

bool Textures::tmpl_frame_render()
{
	// color that gets replaced with
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	// clear all colors
	glClear(GL_COLOR_BUFFER_BIT);

	// bind textures
	m_texture_wall.bind();
	m_texture_face.bind();

	// draw with texture
	glUseProgram(m_gl_program_id);

	// add mixture
	glUniform1f(glGetUniformLocation(m_gl_program_id, "mix_ratio"), m_mixture);

	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	return true;
}

bool Textures::tmpl_clear_resources()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);

	glDeleteVertexArrays(1, &m_vao);

	m_texture_wall.clean_gl();
	m_texture_face.clean_gl();

	return true;
}

bool Textures::tmpl_frame_input()
{
	if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS)
		if (m_mixture < 1)
			m_mixture += .0005f;

	if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS)
		if (m_mixture > 0)
			m_mixture -= .0005f;

	return BasicOpenGLSetup::tmpl_frame_input();
}
