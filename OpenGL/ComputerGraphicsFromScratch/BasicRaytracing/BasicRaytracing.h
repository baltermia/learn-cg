#pragma once

// shared
#include "../../Shared\BasicOpenGLSetup.h"

class BasicRaytracing : public shrd::BasicOpenGLSetup
{
	// template methods
protected:
	bool tmpl_setup() override;
	bool tmpl_frame_render() override;
	bool tmpl_clear_resources() override;

	// template properties
protected:
	// required properties
	std::string_view tmpl_prop_window_name() const override { return "Basic Raytracing"; }

private:
	GLuint m_vao = 0; // vertex array object
	GLuint m_vbo = 0; // vertex buffer object
};
