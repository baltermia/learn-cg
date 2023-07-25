#pragma once

// gl
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// lib
#include "..\..\..\Shared\Shared.h"

class TwoTriangles2 : public shrd::BasicOpenGLSetup
{
	// template methods
protected:
	bool tmpl_setup() override;
	bool tmpl_frame_render() override;
	bool tmpl_clear_resources() override;

	// template properties
protected:
	// required properties
	std::string tmpl_prop_window_name() const override { return "Two Triangles"; }

private:
	GLuint m_vao1 = 0; // vertex array object
	GLuint m_vbo1 = 0; // vertex buffer object
	GLuint m_vao2 = 0; // vertex array object
	GLuint m_vbo2 = 0; // vertex buffer object
};
