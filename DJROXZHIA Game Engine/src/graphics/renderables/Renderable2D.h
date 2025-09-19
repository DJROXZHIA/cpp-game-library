#ifndef DJROXZHIA_RENDERABLE2D
#define DJROXZHIA_RENDERABLE2D

#include "glm/glm/glm.hpp"
#include "graphics/Texture.h"

namespace DJROXZHIA {

	class Renderable2D
	{
	public:
		Renderable2D(const glm::vec3& position, const glm::vec2& size);
		Renderable2D(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		Renderable2D(const glm::vec3& position, const glm::vec2& size, Texture* texture);
		Renderable2D(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, Texture* texture);
		Renderable2D();

		//~Renderable2D();

		inline glm::vec3 GetPositon() const { return p_position; }
		inline void SetPositon(const glm::vec3& position) { p_position = position; }

		inline glm::vec2 GetSize() const { return p_size; }
		inline void SetSize(const glm::vec2& size) { p_size = size; }

		inline glm::vec4 GetColor() const { return p_color; }
		inline void SetColor(const glm::vec4& color) { p_color = color; }

		inline Texture* GetTexture() const { return p_texture; }
		inline void SetTexture(Texture* texture) { p_texture = texture; }

	protected:
		glm::vec3 p_position;
		glm::vec2 p_size;
		glm::vec4 p_color;
		Texture* p_texture;

	};

}

#endif // !DJROXZHIA_RENDERABLE2D
