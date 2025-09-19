#ifndef DJROXZHIA_EVENTS
#define DJROXZHIA_EVENTS

#include "graphics/Window.h"

namespace DJROXZHIA {

	//	KEY EVENT
	class KeyEvent
	{
	public:
		static void Init();
		static void Shutdown();

		static void Update();

		static bool IsKeyPressed(const unsigned int& key);
		static bool IsKeyJustPressed(const unsigned int& key);

	private:
		static bool m_keys[1024];
		static bool m_cantPress[1024];
		static bool m_justPressed[1024];

	private:
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

		friend class Window;
	};


	//	MOUSE EVENT
	class MouseEvent
	{
	public:	
		static void Init();
		static void Shutdown();

		static void Update();

		static bool IsMouseButtonPressed(const unsigned int& button);
		static bool IsMouseButtonJustPressed(const unsigned int& button);

		inline static double GetMouseX() { return m_MouseX; }
		inline static double GetMouseY() { return m_MouseY; }

	private:
		static bool m_mouseButtons[32], m_cantPress[32], m_justPressed[32];
		static double m_MouseX, m_MouseY;

	private:
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

		friend class Window;
	};

}

#endif // !DJROXZHIA_EVENTS
