#ifndef DJROXZHIA_AUDIO_MANAGER
#define DJROXZHIA_AUDIO_MANAGER

#include "miniaudio/miniaudio.h"

namespace DJROXZHIA {

	class AudioManager
	{
	public:
		AudioManager();
		~AudioManager();

		const char* LoadAudio(const char* filepath, const char* audioName);

	private:
		ma_device m_device;
		ma_device_config m_deviceConfig;

	private:
		static void dataCallback(ma_device* device, void* outputBuffer, const void* inputBuffer, ma_uint32 frameCount) 
		{
		}
	};

}

#endif // !DJROXZHIA_AUDIO_MANAGER

