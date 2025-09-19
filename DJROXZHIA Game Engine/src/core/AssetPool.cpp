#include "AssetPool.h"

namespace DJROXZHIA {

	std::unordered_map<const char*, DJROXZHIA::Texture> AssetPool::m_textures = {};
	std::unordered_map<const char*, ImFont*> AssetPool::m_fonts = {};

	void AssetPool::Init()
	{}

	void AssetPool::Shutdown()
	{}

}