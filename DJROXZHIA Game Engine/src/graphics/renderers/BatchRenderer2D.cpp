#include "BatchRenderer2D.h"

namespace DJROXZHIA {

	GLuint BatchRenderer2D::m_vao = 0, BatchRenderer2D::m_vbo = 0, BatchRenderer2D::m_ibo = 0;
	GLuint BatchRenderer2D::m_textures[16] = {};
	GLuint BatchRenderer2D::m_whiteTexture = 0;
	uint32_t BatchRenderer2D::m_indicesCount = 0, BatchRenderer2D::m_nextTextureSlot = 0;
	VertexValues* BatchRenderer2D::m_mappedBuffer = nullptr;

	uint32_t BatchRenderer2D::m_spritesCount = 0, BatchRenderer2D::m_drawCalls = 0;

	void BatchRenderer2D::Shutdown()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &m_vbo);
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &m_vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &m_ibo);
		glBindTexture(GL_TEXTURE_2D, 0);
		glDeleteTextures(1, &m_whiteTexture);
		m_indicesCount = 0;
		m_nextTextureSlot = 0;
		m_spritesCount = 0;
		m_drawCalls = 0;
	}

	void BatchRenderer2D::BeginSession()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		m_mappedBuffer = (VertexValues*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void BatchRenderer2D::Submit(DJROXZHIA::Renderable2D* obj)
	{
		if (m_indicesCount >= RENDERER_INDICES_SIZE || m_nextTextureSlot >= 16)
		{
			EndSession();
			Flush();
			BeginSession();
		}

		glm::vec3 pos = obj->GetPositon();
		glm::vec2 size = obj->GetSize();
		glm::vec4 color = obj->GetColor();
		Texture* texture = obj->GetTexture();

		float textureSlot = 0.0f;
		if (texture != nullptr)
		{
			for (unsigned int i = 1; i < m_nextTextureSlot; i++)
			{
				if (m_textures[i] == texture->GetTextureID())
				{
					textureSlot = (float)i;
					break;
				}
			}

			if (textureSlot == 0.0f)
			{
				textureSlot = (float)m_nextTextureSlot;
				m_textures[m_nextTextureSlot] = texture->GetTextureID();
				m_nextTextureSlot++;
			}
		}

		m_mappedBuffer->position = pos;
		m_mappedBuffer->texture = textureSlot;
		m_mappedBuffer->texCoords = glm::vec2(0.0f, 1.0f);
		m_mappedBuffer->color = color;
		m_mappedBuffer++;

		m_mappedBuffer->position = glm::vec3(pos.x + size.x, pos.y, pos.z);
		m_mappedBuffer->texture = textureSlot;
		m_mappedBuffer->texCoords = glm::vec2(1.0f, 1.0f);
		m_mappedBuffer->color = color;
		m_mappedBuffer++;

		m_mappedBuffer->position = glm::vec3(pos.x + size.x, pos.y + size.y, pos.z);
		m_mappedBuffer->texture = textureSlot;
		m_mappedBuffer->texCoords = glm::vec2(1.0f, 0.0f);
		m_mappedBuffer->color = color;
		m_mappedBuffer++;

		m_mappedBuffer->position = glm::vec3(pos.x, pos.y + size.y, pos.z);
		m_mappedBuffer->texture = textureSlot;
		m_mappedBuffer->texCoords = glm::vec2(0.0f, 0.0f);
		m_mappedBuffer->color = color;
		m_mappedBuffer++;

		m_indicesCount += 6;
		m_spritesCount += 1;
	}

	void BatchRenderer2D::Submit(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, GLuint texture_id)
	{
		if (m_indicesCount >= RENDERER_INDICES_SIZE || m_nextTextureSlot >= 16)
		{
			EndSession();
			Flush();
			BeginSession();
		}

		float textureSlot = 0.0f;
		if (texture_id != m_whiteTexture)
		{
			for (unsigned int i = 1; i < m_nextTextureSlot; i++)
			{
				if (m_textures[i] == texture_id)
				{
					textureSlot = (float)i;
					break;
				}
			}

			if (textureSlot == 0.0f)
			{
				textureSlot = (float)m_nextTextureSlot;
				m_textures[m_nextTextureSlot] = texture_id;
				m_nextTextureSlot++;
			}
		}

		m_mappedBuffer->position = position;
		m_mappedBuffer->texture = textureSlot;
		m_mappedBuffer->texCoords = glm::vec2(0.0f, 1.0f);
		m_mappedBuffer->color = color;
		m_mappedBuffer++;

		m_mappedBuffer->position = glm::vec3(position.x + size.x, position.y, position.z);
		m_mappedBuffer->texture = textureSlot;
		m_mappedBuffer->texCoords = glm::vec2(1.0f, 1.0f);
		m_mappedBuffer->color = color;
		m_mappedBuffer++;

		m_mappedBuffer->position = glm::vec3(position.x + size.x, position.y + size.y, position.z);
		m_mappedBuffer->texture = textureSlot;
		m_mappedBuffer->texCoords = glm::vec2(1.0f, 0.0f);
		m_mappedBuffer->color = color;
		m_mappedBuffer++;

		m_mappedBuffer->position = glm::vec3(position.x, position.y + size.y, position.z);
		m_mappedBuffer->texture = textureSlot;
		m_mappedBuffer->texCoords = glm::vec2(0.0f, 0.0f);
		m_mappedBuffer->color = color;
		m_mappedBuffer++;

		m_indicesCount += 6;
		m_spritesCount += 1;
	}

	void BatchRenderer2D::Submit(const glm::mat4& transform, const glm::vec4& color, GLuint texture_id)
	{
		if (m_indicesCount >= RENDERER_INDICES_SIZE || m_nextTextureSlot >= 16)
		{
			EndSession();
			Flush();
			BeginSession();
		}

		float textureSlot = 0.0f;
		if (texture_id != m_whiteTexture)
		{
			for (unsigned int i = 1; i < m_nextTextureSlot; i++)
			{
				if (m_textures[i] == texture_id)
				{
					textureSlot = (float)i;
					break;
				}
			}

			if (textureSlot == 0.0f)
			{
				textureSlot = (float)m_nextTextureSlot;
				m_textures[m_nextTextureSlot] = texture_id;
				m_nextTextureSlot++;
			}
		}

		m_mappedBuffer->position = transform * glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f);
		m_mappedBuffer->texture = textureSlot;
		m_mappedBuffer->texCoords = glm::vec2(0.0f, 1.0f);
		m_mappedBuffer->color = color;
		m_mappedBuffer++;

		m_mappedBuffer->position = transform * glm::vec4(0.5f, -0.5f, 0.0f, 1.0f);
		m_mappedBuffer->texture = textureSlot;
		m_mappedBuffer->texCoords = glm::vec2(1.0f, 1.0f);
		m_mappedBuffer->color = color;
		m_mappedBuffer++;

		m_mappedBuffer->position = transform * glm::vec4(0.5f, 0.5f, 0.0f, 1.0f);
		m_mappedBuffer->texture = textureSlot;
		m_mappedBuffer->texCoords = glm::vec2(1.0f, 0.0f);
		m_mappedBuffer->color = color;
		m_mappedBuffer++;

		m_mappedBuffer->position = transform * glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f);
		m_mappedBuffer->texture = textureSlot;
		m_mappedBuffer->texCoords = glm::vec2(0.0f, 0.0f);
		m_mappedBuffer->color = color;
		m_mappedBuffer++;

		m_indicesCount += 6;
		m_spritesCount += 1;
	}

	void BatchRenderer2D::EndSession()
	{
		if (glUnmapBuffer(GL_ARRAY_BUFFER) != GL_TRUE)
		{
			std::cerr << "ERROR::BATCH_RENDERER::GLUNMAPBUFFER\n";
			return;
		}
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void BatchRenderer2D::Flush()
	{
		for (unsigned int i = 0; i < m_nextTextureSlot; i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, m_textures[i]);
		}

		glBindVertexArray(m_vao);
		glDrawElements(GL_TRIANGLES, m_indicesCount, GL_UNSIGNED_INT, NULL);
		glBindVertexArray(0);

		m_indicesCount = 0;
		m_spritesCount = 0;
		m_nextTextureSlot = 1;
	}

	void BatchRenderer2D::Init()
	{
		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);
		glGenBuffers(1, &m_ibo);

		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
		glEnableVertexAttribArray(SHADER_TEXTURE_INDEX);
		glEnableVertexAttribArray(SHADER_TEXTURE_COORDS_INDEX);
		glEnableVertexAttribArray(SHADER_COLOR_INDEX);

		glVertexAttribPointer(SHADER_VERTEX_INDEX,			3, GL_FLOAT, GL_FALSE, sizeof(VertexValues), (void*)offsetof(VertexValues, position));
		glVertexAttribPointer(SHADER_TEXTURE_INDEX,			1, GL_FLOAT, GL_FALSE, sizeof(VertexValues), (void*)offsetof(VertexValues, texture));
		glVertexAttribPointer(SHADER_TEXTURE_COORDS_INDEX,	2, GL_FLOAT, GL_FALSE, sizeof(VertexValues), (void*)offsetof(VertexValues, texCoords));
		glVertexAttribPointer(SHADER_COLOR_INDEX,			4, GL_FLOAT, GL_FALSE, sizeof(VertexValues), (void*)offsetof(VertexValues, color));

		unsigned int* indices = new unsigned int[RENDERER_INDICES_SIZE];
		int offset = 0;
		for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
		{
			indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;
			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, RENDERER_INDICES_SIZE * sizeof(unsigned int), indices, GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		delete[] indices;


		glGenTextures(1, &m_whiteTexture);

		glActiveTexture(GL_TEXTURE0 + 0);
		glBindTexture(GL_TEXTURE_2D, m_whiteTexture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		uint32_t color = 0xffffffff;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &color);

		m_textures[0] = m_whiteTexture;
		m_nextTextureSlot = 1;
	}

}