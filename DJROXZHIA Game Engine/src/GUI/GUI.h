#ifndef DJROXZHIA_GUI
#define DJROXZHIA_GUI

#include "graphics/Window.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

namespace DJROXZHIA {

	class GUI
	{
	public:
		static void Init(Window* window);
		static void Shutdown();

		static void BeginSession();
		static void EndSession();

		static inline ImGuiIO& GetImGuiIO() { return ImGui::GetIO(); }

	private:
		static Window* m_window;
	};

}

#endif // !DJROXZHIA_GUI
