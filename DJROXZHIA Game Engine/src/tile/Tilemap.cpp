#include "Tilemap.h"

#include <sstream>
#include <vector>
#include <iostream>

#include "graphics/renderers/BatchRenderer2D.h"

#include "utils/FileUtils.h"

namespace DJROXZHIA {

	TileMap::TileMap(const char* path)
		: m_path(path)
	{
		std::string file = FileUtils::ReadFile(path);
		
		std::vector<unsigned int> data;

		std::stringstream s(file);
		std::string word;
		while (s >> word)
		{
			unsigned int a = std::stoi(word);
			data.push_back(a);
		}

		m_mapWidth = data[0];
		m_mapHeight = data[1];

		m_data = new int* [m_mapWidth];
		for (int i = 0; i < m_mapWidth; i++)
			m_data[i] = new int[m_mapHeight];

		for (int x = 0; x < m_mapWidth; x++)
		{
			for (int y = 0; y < m_mapHeight; y++)
			{
				if (data.size() > (x + y * m_mapHeight) + 2)
				{
					if (data[(x + y * m_mapHeight) + 2] != NULL)
					{
						m_data[x][y] = data[(x + y * m_mapHeight) + 2];
					}
					else
						m_data[x][y] = 0;
				}
				else
					m_data[x][y] = 0;
			}
		}
	}

	TileMap::~TileMap()
	{
		delete[] m_data;
	}

	void TileMap::Update()
	{
		for (auto tile : m_tiles)
		{
			tile.second.Update();
		}
	}

	void TileMap::Render()
	{
		for (auto tile : m_tiles)
		{
			tile.second.Render();
		}

		for (int x = 0; x < m_mapWidth; x++)
		{
			for (int y = 0; y < m_mapHeight; y++)
			{
				int height = GetTile(x, y)->GetHeight();
				int width = GetTile(x, y)->GetWidth();
				glm::vec3 translation(x * width, y * height, -1.0f);
				BatchRenderer2D::Submit(translation, glm::vec2(width, height), glm::vec4(1.0f), GetTile(x, y)->GetTextureID());
			}
		}
	}
}