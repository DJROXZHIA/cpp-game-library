#ifndef DJROXZHIA_TILE
#define DJROXZHIA_TILE

#include "graphics/Texture.h"

namespace DJROXZHIA {

	class Tile
	{
	public:
		Tile(const int& id, const int& width, const int& height, Texture* texture, const bool& isSolid);
		Tile() = default;

		virtual void Update() {};
		virtual void Render() {};

		inline int GetID() const { return m_id; }
		inline void SetID(const int& id) { m_id = id; }

		inline GLuint GetTextureID() const { return m_textureID; }
		inline void SetTextureID(const GLuint& texture) { m_textureID = texture; }

		inline bool IsSolid() const { return m_isSolid; }
		inline void SetSolid(const bool& isSolid) { m_isSolid = isSolid; }

		inline int GetHeight() const { return m_height; }
		inline void SetHeight(const int& height) { m_height = height; }

		inline int GetWidth() const { return m_width; }
		inline void SetWidth(const int& width) { m_width = width; }

	protected:
		int m_id;
		GLuint m_textureID;
		bool m_isSolid;
		int m_width, m_height;

	};

}

#endif // !DJROXZHIA_TILE
