#ifndef DJROXZHIA_APPLICATION
#define DJROXZHIA_APPLICATION

#include "graphics/Window.h"

#include "glm/glm/glm.hpp"

namespace DJROXZHIA {

	class Application
	{
	public:
		Application(Window* window);
		~Application();

		bool Run(const glm::vec4& color);

		double GetTime();
		double GetDelta();

	private:
		double m_currentTime, m_lastTime, m_delta;
		Window* m_window;

	};

}

#endif // !DJROXZHIA_APPLICATION
