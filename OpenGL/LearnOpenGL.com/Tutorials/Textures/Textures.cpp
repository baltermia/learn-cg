#include "Textures.h"

// shrd
#include "..\..\..\Shared\Vec.h"
#include "..\..\..\Shared\Texture2D.h"

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
	// Load Texture

	Texture2D("./Resources/texture.jpg")
		.load_into_gl()
		.bind_id(&m_texture)
		.clean();

	return true;
}

bool Textures::tmpl_frame_render()
{
	// color that gets replaced with
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	// clear all colors
	glClear(GL_COLOR_BUFFER_BIT);

	// bind texture
	glBindTexture(GL_TEXTURE_2D, m_texture);

	// draw with texture
	glUseProgram(m_gl_program_id);
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	return true;
}

bool Textures::tmpl_clear_resources()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);

	glDeleteVertexArrays(1, &m_vao);

	glDeleteTextures(1, &m_texture);

	return true;
}
