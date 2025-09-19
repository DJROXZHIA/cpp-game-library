#ifndef DJROXZHIA_TILEMAP
#define DJROXZHIA_TILEMAP

#include "Tile.h"
#include <unordered_map>

namespace DJROXZHIA {

	class TileMap
	{
	public:
		TileMap(const char* path);
		~TileMap();

		void Update();
		void Render();

		inline unsigned int GetMapWidth() { return m_mapWidth; }
		inline unsigned int GetMapHeight() { return m_mapHeight; }
		inline int** getdata() { return m_data; }

		inline void SetTile(const int id, const Tile& tile) { m_tiles[id] = tile; }

		inline int GetTileID(const int& x, const int& y) { return m_data[x][y]; }
		inline Tile* GetTile(const int& x, const int& y) { return &m_tiles[m_data[x][y]]; }

	private:
		unsigned int m_mapWidth, m_mapHeight;
		const char* m_path;
		int** m_data;

		std::unordered_map<int, Tile> m_tiles;
	};

}

#endif // !DJROXZHIA_TILEMAP

