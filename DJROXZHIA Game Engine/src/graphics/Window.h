#ifndef DJROXZHIA_WINDOW
#define DJROXZHIA_WINDOW

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>

#include <iostream>

namespace DJROXZHIA {

	class Window
	{
	public:
		Window(const char* title, const int& width, const int& height, const int& aspect_w, const int& aspect_h, const bool& vsync, const bool& fullscreen);
		~Window();

		void Clear(const glm::vec4& color);
		void Update();
		bool IsWindowClosed();
		void CloseWindow();

		inline int GetWidth() { return m_width; }
		inline void SetWidth(const int& width) { m_width = width; }
		inline int GetHeight() { return m_height; }
		inline void SetHeight(const int& height) { m_height = height; }

		inline int GetAspectW() { return m_aspectW; }
		inline void SetAspectW(const int& aspectW) { m_aspectW = aspectW; }
		inline int GetAspectH() { return m_aspectH; }
		inline void SetAspectH(const int& aspectH) { m_aspectH = aspectH; }

		inline GLFWwindow* getWindow() { return m_window; }

		inline bool IsFullScreen() { return m_fullscreen; }
		inline void SetFullScreen(const bool& fullscreen) { m_fullscreen = fullscreen; }

		inline int GetScreenWidth() { return m_mode->width; }
		inline int GetScreenHeight() { return m_mode->height; }

	private:
		static int m_width, m_height; 
		int m_aspectW, m_aspectH;
		const char* m_title;

		bool m_vsync, m_fullscreen;

		GLFWwindow* m_window;
		GLFWmonitor* m_monitor;
		const GLFWvidmode* m_mode;

	private:
		bool Init();

		static void Resize(GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
			m_width = width;
			m_height = height;
		}
	};

}

#endif // !DJROXZHIA_WINDOW
