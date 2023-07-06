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

	// template properties
protected:
	// required properties
	std::string tmpl_prop_window_name() override { return "Hello Triangle"; }

private:
	GLuint m_vao = 0; // vertex array object
	GLuint m_ebo = 0; // element buffer object
};
