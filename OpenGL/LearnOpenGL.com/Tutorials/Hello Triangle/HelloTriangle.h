#pragma once

// gl
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// lib
#include "..\..\..\Shared\Shared.h"

class HelloTriangle : public shrd::BasicOpenGLSetup
{
	// template methods
protected:
	bool tmpl_setup() override;
	bool tmpl_frame_render() override;
	bool tmpl_clear_resources() override;

	// template properties
protected:
	// required properties
	std::string tmpl_prop_window_name() override { return "Hello Triangle"; }

private:
	GLuint m_vao = 0; // vertex array object
	GLuint m_vbo = 0; // vertex array objcet
};
