#include "InputEvent.h"

#include <iostream>

namespace DJROXZHIA {

	bool KeyEvent::m_keys[1024] = {};
	bool KeyEvent::m_cantPress[1024] = {};
	bool KeyEvent::m_justPressed[1024] = {};

	bool MouseEvent::m_mouseButtons[32] = {};
	bool MouseEvent::m_cantPress[32] = {};
	bool MouseEvent::m_justPressed[32] = {};
	double MouseEvent::m_MouseX = 0.0;
	double MouseEvent::m_MouseY = 0.0;


	//	KEY EVENT
	void KeyEvent::Init()
	{
		memset(m_keys, false, sizeof(m_keys));
	}

	void KeyEvent::Shutdown(){}

	void KeyEvent::Update()
	{
		for (unsigned int i = 0; i < 1024; i++)
		{
			if (m_cantPress[i] && !m_keys[i])
			{
				m_cantPress[i] = false;
			}
			else if (m_justPressed[i])
			{
				m_cantPress[i] = true;
				m_justPressed[i] = false;
			}
			if (!m_cantPress[i] && m_keys[i])
			{
				m_justPressed[i] = true;
			}
		}
	}

	bool KeyEvent::IsKeyPressed(const unsigned int& key)
	{
		if (key >= 1024)
			return false;
		else
			return m_keys[key];
	}

	bool KeyEvent::IsKeyJustPressed(const unsigned int& key)
	{
		if (key >= 1024)
			return false;
		else
			return m_justPressed[key];
	}

	void KeyEvent::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		m_keys[key] = action != GLFW_RELEASE;
	}


	//	MOUSE EVENT
	void MouseEvent::Init()
	{
		memset(m_mouseButtons, false, sizeof(m_mouseButtons));
		memset(m_cantPress, false, sizeof(m_cantPress));
		memset(m_justPressed, false, sizeof(m_justPressed));
		m_MouseX = 0.0f;
		m_MouseY = 0.0f;
	}

	void MouseEvent::Shutdown() {}

	void MouseEvent::Update()
	{
		for (unsigned int i = 0; i < 32; i++)
		{
			if (m_cantPress[i] && !m_mouseButtons[i])
			{
				m_cantPress[i] = false;
			}
			else if (m_justPressed[i])
			{
				m_cantPress[i] = true;
				m_justPressed[i] = false;
			}
			if (!m_cantPress[i] && m_mouseButtons[i])
			{
				m_justPressed[i] = true;
			}
		}
	}

	bool MouseEvent::IsMouseButtonPressed(const unsigned int& button)
	{
		if (button >= 32)
			return false;
		else
			return m_mouseButtons[button];
	}

	bool MouseEvent::IsMouseButtonJustPressed(const unsigned int& button)
	{
		if (button >= 32)
			return false;
		else
			return m_justPressed[button];
	}

	void MouseEvent::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		m_mouseButtons[button] = action != GLFW_RELEASE;
	}

	void MouseEvent::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		m_MouseX = xpos;
		m_MouseY = ypos;
	}
}