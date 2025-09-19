#ifndef DJROXZHIA_TEXTURE
#define DJROXZHIA_TEXTURE

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "stb_image/stb_image.h"

#include <iostream>

namespace DJROXZHIA {

	class Texture
	{
	public:
		Texture();
		Texture(std::string path);
		Texture(GLuint id);
		Texture(const Texture& other);

		~Texture();

		void Use(int slot);

		inline const int  GetWidth() const { return m_Width; }
		inline const int  GetHeight() const { return m_Height; }
		inline void SetWidth(const int& width) { m_Width = width; }
		inline void SetHeight(const int& height) { m_Height = height; }

		inline const GLuint GetTextureID() const { return m_textureID; }

		inline std::string GetPath() const { return m_path; }

		inline bool IsBlank() const { return m_isBlank; }


	private:
		GLuint m_textureID;

		unsigned char* m_Buffer;
		int m_Width, m_Height, m_BPP;

		bool m_isBlank = false;

		std::string m_path;

	private:
		bool LoadTexture();

	};

}


#endif // !DJROXZHIA_TEXTURE