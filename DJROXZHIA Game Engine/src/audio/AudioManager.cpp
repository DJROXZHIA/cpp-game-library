#include "AudioManager.h"

#include <iostream>

namespace DJROXZHIA {

	AudioManager::AudioManager()
	{
        m_deviceConfig = ma_device_config_init(ma_device_type_playback);
        m_deviceConfig.playback.format = ma_format_f32;
        m_deviceConfig.playback.channels = 2;
        m_deviceConfig.sampleRate = 44100;
        m_deviceConfig.dataCallback = dataCallback;
        m_deviceConfig.pUserData = m_device.pUserData;

        if (ma_device_init(NULL, &m_deviceConfig, &m_device) != MA_SUCCESS) {
            std::cout << "ERROR::AUDIO::CANNOT INITIALIZE DEVICE!\n";
            return;
        }

        ma_device_start(&m_device);
	}

    AudioManager::~AudioManager()
    {
        ma_device_uninit(&m_device);
    }

    const char* AudioManager::LoadAudio(const char* filepath, const char* audioName)
    {
        ma_decoder_config config = ma_decoder_config_init(ma_format_f32, 2, m_deviceConfig.sampleRate);

        ma_decoder decoder;
        if (ma_decoder_init_file(filepath, &config, &decoder) != MA_SUCCESS) {
            std::cout << "ERROR::AUDIO::COULDN'T INITIALIZE FILE! FILEPATH = \"" << filepath << "\"\n";
        }

        return audioName;
    }

}