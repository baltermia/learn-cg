#pragma once

// gl
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// std
#include <utility>
#include <string_view>

namespace shrd
{
	class BasicOpenGLSetup
	{
	public:
		/// <summary>
		/// Default constructor taking two optional paramteres defining the Window size
		/// </summary>
		BasicOpenGLSetup(int width = 800, int height = 600);

		/// <summary>
		/// Initializes OpenGL, GLAD & GLFW and creates a Window
		/// </summary>
		/// <returns>Success</returns>
		bool initialize();

		/// <summary>
		/// Runs the OpenGL Code
		/// </summary>
		/// <returns>Success</returns>
		bool run();

		/// <summary>
		/// Cleans up any allocated resources. The object should not receive any further calls
		/// </summary>
		/// <returns>Success</returns>
		bool clean();

	// properties
	public:
		inline std::pair<int, int> prop_window_size()	const	{ return m_window_size; }
		inline std::string_view prop_window_name()		const	{ return tmpl_prop_window_name(); }

	// template methods
	protected:
		virtual inline bool tmpl_setup()			{ return true; }
		virtual inline bool tmpl_frame_render()		{ return true; }
		virtual inline bool tmpl_frame_input();
		virtual inline bool tmpl_clear_resources()	{ return true; }
		/// <summary>
		/// Either override this function to manually load the shaders or create shader.vert/.frag files to only override the default shaders
		/// </summary>
		virtual inline bool tmpl_load_shaders();

	// template properties
	protected:
		// required properties
		virtual inline std::string_view tmpl_prop_window_name() const = 0;

		// optional properties
		virtual inline std::pair<int, int> tmpl_prop_opengl_version() const { return { 4, 6 }; };

	protected:
		GLFWwindow* m_window = nullptr;
		GLuint m_gl_program_id = 0;

	private:
		static void callback_framebuffer_size_changed(GLFWwindow* window, int width, int height);

		std::pair<int, int> m_window_size;
	};
}