#include "Tile.h"

namespace DJROXZHIA {

	Tile::Tile(const int& id, const int& width, const int& height, Texture* texture, const bool& isSolid)
		: m_id(id), m_width(width), m_height(height), m_textureID(texture->GetTextureID()), m_isSolid(isSolid)
	{}

}