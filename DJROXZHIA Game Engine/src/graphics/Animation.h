#ifndef DJROXZHIA_ANIMATION
#define DJROXZHIA_ANIMATION

#include "graphics/Texture.h"

#include <vector>

namespace DJROXZHIA {

	class Animation
	{
	public:
		Animation(const double& time, const uint32_t& speed, std::vector<Texture> frames);
		~Animation() {};

		void Update(const double& time);
		Texture* GetFrame();
	private:
		uint32_t m_speed, m_index;
		double m_lastTime, m_timer;
		std::vector<Texture> m_frames;
	};

}

#endif // !DJROXZHIA_ANIMATION

