#include "Texture.h"
#include "utils/FileUtils.h"
#include "graphics/renderers/BatchRenderer2D.h"

namespace DJROXZHIA {

	Texture::Texture()
		: m_Width(0), m_Height(0), m_BPP(0), m_Buffer(nullptr), m_path("")
	{
		m_isBlank = true;
		m_textureID = BatchRenderer2D::GetDefaultTexture();
	}

	Texture::Texture(std::string path)
		: m_Width(0), m_Height(0), m_BPP(0), m_Buffer(nullptr), m_path(path)
	{
		if (!LoadTexture())
		{
			std::cerr << "ERROR::TEXTURE::NOT LOADED!\n";
		}
	}

	Texture::Texture(GLuint id)
		: m_textureID(id), m_BPP(0), m_Buffer(nullptr), m_Height(0), m_Width(0), m_path("Generated")
	{
	}

	Texture::Texture(const Texture& other)
	{
		m_Height = other.m_Height;
		m_Width = other.m_Width;
		m_isBlank = other.m_isBlank;
		m_path = other.m_path;
		m_textureID = other.m_textureID;
	}

	Texture::~Texture()
	{
		//glBindTexture(GL_TEXTURE_2D, 0);
		//glDeleteTextures(1, &m_textureID);
	}

	void Texture::Use(int slot)
	{
		if (slot <= 0)
			slot = 0;
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_textureID);
	}

	bool Texture::LoadTexture()
	{
		if (DJROXZHIA::FileUtils::CheckExtension(m_path, { "png", "jpg", "jpeg" }))
		{
			stbi_set_flip_vertically_on_load(true);
			m_Buffer = stbi_load(m_path.c_str(), &m_Width, &m_Height, &m_BPP, 0);

			if (m_Buffer)
			{
				GLenum format = GL_RGB;
				if (m_BPP == 1)
					format = GL_RED;
				else if (m_BPP == 3)
					format = GL_RGB;
				else if (m_BPP == 4)
					format = GL_RGBA;

				glGenTextures(1, &m_textureID);
				glBindTexture(GL_TEXTURE_2D, m_textureID);
				glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, m_Buffer);
				glGenerateMipmap(GL_TEXTURE_2D);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glBindTexture(GL_TEXTURE_2D, 0);
				stbi_image_free(m_Buffer);
			}
			else
			{
				std::cerr << "ERROR::TEXTURE::FAILED TO LOAD IMAGE! PATH=\"" << m_path << "\"\n";
				stbi_image_free(m_Buffer);
				return false;
			}
		}
		else
		{
			std::cerr << "ERROR::DJROXZHIA GAME ENGINE DOESN'T SUPPORT THAT IMAGE EXTENSION YET!" << "\n";
			return false;
		}
		return true;
	}

}