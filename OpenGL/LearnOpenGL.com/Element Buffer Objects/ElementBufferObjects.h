#pragma once

// gl
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// lib
#include "..\..\Shared\Shared.h"

class ElementBufferObjects : public shrd::BasicOpenGLSetup
{
	// template methods
protected:
	bool tmpl_setup() override;
	bool tmpl_frame_render() override;
	bool tmpl_clear_resources() override;

	// template properties
protected:
	// required properties
	std::string tmpl_prop_window_name() override { return "Element Buffer Object"; }

private:
	GLuint m_vao = 0; // vertex array object
	GLuint m_ebo = 0; // element buffer object
	GLuint m_vbo = 0; // vertex array objcet
	GLuint m_vertex_shader = 0;
	GLuint m_fragment_shader = 0;

};
