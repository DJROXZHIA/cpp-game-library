#include "Application.h"

#include "core/events/InputEvent.h"

namespace DJROXZHIA {

	Application::Application(Window* window)
		: m_window(window)
	{
		KeyEvent::Init();
		MouseEvent::Init();
		m_lastTime = glfwGetTime();
	}

	Application::~Application()
	{
		KeyEvent::Shutdown();
		MouseEvent::Shutdown();
	}

	double Application::GetTime()
	{
		return glfwGetTime();
	}

	double Application::GetDelta()
	{
		return m_delta;
	}

	bool Application::Run(const glm::vec4& color)
	{
		if (!m_window->IsWindowClosed())
		{
			m_window->Clear(color);
			DJROXZHIA::KeyEvent::Update();
			DJROXZHIA::MouseEvent::Update();

			m_currentTime = glfwGetTime();
			m_delta = m_currentTime - m_lastTime;
			m_lastTime = glfwGetTime();

			return true;
		}
		return false;
	}

}