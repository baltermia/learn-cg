#pragma once

// lib
#include "..\..\..\Shared\Shared.h"

class TwoColorTriangles : public shrd::BasicOpenGLSetup
{
	// template methods
protected:
	bool tmpl_setup() override;
	bool tmpl_frame_render() override;
	bool tmpl_clear_resources() override;
    bool tmpl_load_shaders() override;
    
	// template properties
protected:
	// required properties
	std::string_view tmpl_prop_window_name() const override { return "Two Color Triangles"; }

private:
	GLuint m_gl_program_id_2; // second opengl program
	GLuint m_vao1 = 0; // vertex array object
	GLuint m_vbo1 = 0; // vertex buffer object
	GLuint m_vao2 = 0; // vertex array object
	GLuint m_vbo2 = 0; // vertex buffer object
};
