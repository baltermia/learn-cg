#pragma once

// shared
#include "..\..\..\Shared\BasicOpenGLSetup.h"
#include "..\..\..\Shared\Texture2D.h"

class Textures : public shrd::BasicOpenGLSetup
{
	// template methods
protected:
	bool tmpl_setup() override;
	bool tmpl_frame_render() override;
	bool tmpl_clear_resources() override;

	// template properties
protected:
	// required properties
	std::string_view tmpl_prop_window_name() const override { return "Textures"; }

private:
	GLuint m_vao = 0; // vertex array object
	GLuint m_vbo = 0; // vertex buffer object
	GLuint m_ebo = 0; // element buffer object
	Texture2D m_texture_wall; // wall texture
	Texture2D m_texture_face;
};
