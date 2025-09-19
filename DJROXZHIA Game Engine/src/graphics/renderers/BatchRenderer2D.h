#ifndef DJROXZHIA_BATCHRENDERER2D
#define DJROXZHIA_BATCHRENDERER2D

#include "maths/Geometry.h"

#include "graphics/renderables/Renderable2D.h"
#include "graphics/Shader.h"

namespace DJROXZHIA {
	
	struct VertexValues
	{
		glm::vec3 position;
		float texture;
		glm::vec2 texCoords;
		glm::vec4 color;
	};

	class BatchRenderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginSession();
		static void Submit(Renderable2D* obj);
		static void Submit(const glm::mat4& transform, const glm::vec4& color, GLuint texture_id);
		static void Submit(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, GLuint texture_id);
		static void Flush();
		static void EndSession();

		static inline GLuint GetDefaultTexture() { return m_whiteTexture; }

	private:

		static const unsigned int RENDERER_MAX_SPRITES			=		10000;
		static const unsigned int RENDERER_MAX_VERTICES			=		RENDERER_MAX_SPRITES * 4;
		static const unsigned int RENDERER_VERTEX_SIZE			=		sizeof(Vertex);
		static const unsigned int RENDERER_SPRITE_SIZE			=		RENDERER_VERTEX_SIZE * 4;
		static const unsigned int RENDERER_INDICES_SIZE			=		6 * RENDERER_MAX_SPRITES;
		static const unsigned int RENDERER_BUFFER_SIZE			=		RENDERER_MAX_VERTICES * RENDERER_VERTEX_SIZE;
		
		static const unsigned int SHADER_VERTEX_INDEX			=		0;
		static const unsigned int SHADER_TEXTURE_INDEX			=		1;
		static const unsigned int SHADER_TEXTURE_COORDS_INDEX	=		2;
		static const unsigned int SHADER_COLOR_INDEX			=		3;

		static GLuint m_vao, m_vbo, m_ibo;
		static uint32_t m_indicesCount, m_nextTextureSlot;
		static VertexValues* m_mappedBuffer;
		static GLuint m_textures[16];
		static GLuint m_whiteTexture;

		static uint32_t m_spritesCount, m_drawCalls;
	};

}

#endif // !DJROXZHIA_BATCHRENDERER2D
