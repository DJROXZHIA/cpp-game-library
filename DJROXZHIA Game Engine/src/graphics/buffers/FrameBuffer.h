#ifndef DJROXZHIA_FRAMEBUFFER
#define DJROXZHIA_FRAMEBUFFER

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "graphics/Texture.h"

namespace DJROXZHIA { 

	class FrameBuffer
	{
	public:
		FrameBuffer(uint32_t width, uint32_t height);
		~FrameBuffer();

		void Bind();
		void Unbind();

		inline GLuint GetID() { return m_id; }
		inline GLuint GetTextureID() { return m_textureID; }

		inline uint32_t getWidth() { return m_width; }
		inline uint32_t getHeight() { return m_height; }

	private:
		uint32_t m_width, m_height;

		GLuint m_id, m_renderBufferID, m_textureID;
	};

}

#endif // !DJROXZHIA_FRAMEBUFFER

