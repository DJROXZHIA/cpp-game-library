#ifndef DJROXZHIA_ASSETPOOL
#define DJROXZHIA_ASSETPOOL

#include <unordered_map>

#include "graphics/Texture.h"
#include "GUI/GUI.h"

namespace DJROXZHIA {

	class AssetPool 
	{
	public:
		static void Init();
		static void Shutdown();

		static inline void LoadTexture(const char* filepath, const char* texture_name) { m_textures.emplace(texture_name, Texture(filepath)); }
		static inline Texture* GetTexture(const char* texture_name) { return &m_textures[texture_name]; }

		static inline void LoadFont(const char* filepath, const char* font_name, float size)
		{
			m_fonts.emplace(font_name, GUI::GetImGuiIO().Fonts->AddFontFromFileTTF(filepath, size));
		}
		static inline ImFont* GetFont(const char* font_name) { return m_fonts[font_name]; }

	private:
		static std::unordered_map<const char*, DJROXZHIA::Texture> m_textures;
		static std::unordered_map<const char*, ImFont*> m_fonts;
	};

}

#endif // !DJROXZHIA_ASSETPOOL
