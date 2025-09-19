#include "EventSystem.h"

namespace DJROXZHIA {

	void EventSystem::Publish(const char* event_name, void* event_data)
	{
		auto func = m_EventCallbacks[event_name];
		func(event_data);
	}

}