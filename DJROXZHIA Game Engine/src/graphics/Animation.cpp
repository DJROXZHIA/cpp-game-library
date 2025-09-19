#include "Animation.h"

namespace DJROXZHIA {

	Animation::Animation(const double& time, const uint32_t& speed, std::vector<Texture> frames)
		: m_speed(speed), m_frames(frames), m_index(0), m_lastTime(time), m_timer(0)
	{
	}

	void Animation::Update(const double& time)
	{
		m_timer += time - m_lastTime;
		m_lastTime = time;

		if (m_timer > m_speed)
		{
			m_index++;
			m_timer = 0;
			if (m_index >= m_frames.size())
			{
				m_index = 0;
			}
		}
	}

	Texture* Animation::GetFrame()
	{
		return &m_frames[m_index];
	}

}