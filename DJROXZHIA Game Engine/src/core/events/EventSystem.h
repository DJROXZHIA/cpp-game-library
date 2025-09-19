#ifndef DJROXZHIA_EVENT_SYSTEM
#define DJROXZHIA_EVENT_SYSTEM

#include <functional>
#include<unordered_map>

namespace DJROXZHIA {

	using EventCallback = std::function<void(void*)>;

	class EventSystem
	{
	public:
		
		EventSystem() = default;

		inline const char* AddRecipient(const char* event_name, EventCallback callback) { m_EventCallbacks.emplace(event_name, callback); return event_name; }
		inline const char* RemoveRecipient(const char* event_name) { m_EventCallbacks.erase(event_name); return event_name; }
		void Publish(const char* event_name, void* event_data);

	private:
		std::unordered_map<const char*, EventCallback> m_EventCallbacks;
	};

}

#endif // !DJROXZHIA_EVENT_SYSTEM
