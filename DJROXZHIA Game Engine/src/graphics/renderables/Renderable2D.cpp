#include "Renderable2D.h"

namespace DJROXZHIA {

	Renderable2D::Renderable2D(const glm::vec3& position, const glm::vec2& size)
		: p_position(position), p_size(size), p_color(glm::vec4(1.0f)), p_texture(nullptr) {}

	Renderable2D::Renderable2D(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
		: p_position(position), p_size(size), p_color(color), p_texture(nullptr) {}

	Renderable2D::Renderable2D(const glm::vec3& position, const glm::vec2& size, Texture* texture)
		: p_position(position), p_size(size), p_color(glm::vec4(1.0f)), p_texture(texture) {}

	Renderable2D::Renderable2D(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, Texture* texture)
		: p_position(position), p_size(size), p_color(color), p_texture(texture) {}

	Renderable2D::Renderable2D()
		: p_position(glm::vec3(0.0f)), p_size(glm::vec2(1.0f)), p_color(glm::vec4(1.0f)), p_texture(nullptr) {}
}