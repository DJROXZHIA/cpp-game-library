#include "Window.h"

#include "core/events/InputEvent.h"

namespace DJROXZHIA {

	int Window::m_width = 0;
	int Window::m_height = 0;

	Window::Window(const char* title, const int& width, const int& height, const int& aspect_w, const int& aspect_h, const bool& vsync, const bool& fullscreen)
		: m_title(title), m_aspectW(aspect_w), m_aspectH(aspect_h), m_vsync(vsync), m_fullscreen(fullscreen)
	{
		m_width = width;
		m_height = height;
		if (!Init())
		{
			std::cerr << "ERROR::GAME WINDOW NOT INITIALIZED!\n";
			glfwTerminate();
		}
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	void Window::Clear(const glm::vec4& color)
	{
		glClearColor(color.x, color.y, color.z, color.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	bool Window::IsWindowClosed()
	{
		return glfwWindowShouldClose(m_window);
	}

	void Window::Update()
	{
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	void Window::CloseWindow()
	{
		glfwTerminate();
	}

	bool Window::Init()
	{
		if (!glfwInit())
		{
			std::cerr << "ERROR::GLFW INITIALIZATION FAILED!\n";
			glfwTerminate();
			return false;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		m_monitor = glfwGetPrimaryMonitor();
		m_mode = glfwGetVideoMode(m_monitor);

		m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);

		if (m_window == NULL)
		{
			std::cerr << "ERROR::WINDOW IS NULL!\n";
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(m_window);
		glfwSetWindowSizeCallback(m_window, Window::Resize);
		glfwSetKeyCallback(m_window, KeyEvent::KeyCallback);
		glfwSetMouseButtonCallback(m_window, MouseEvent::mouse_button_callback);
		glfwSetCursorPosCallback(m_window, MouseEvent::cursor_position_callback);

		if (m_fullscreen)
		{
			glfwSetWindowMonitor(m_window, m_monitor, 0, 0, m_mode->width, m_mode->height, m_mode->refreshRate);
		}

		if (m_vsync)
		{
			glfwSwapInterval(1);
		}

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "ERROR::GLAD NOT INITIALIZED!\n";
			glfwTerminate();
			return false;
		}

		glfwGetWindowSize(m_window, &m_width, &m_height);
		glViewport(0, 0, m_width, m_height);

		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_STENCIL_TEST);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

		return true;

	}
}