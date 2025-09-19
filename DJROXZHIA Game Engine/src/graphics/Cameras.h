#ifndef DJROXZHIA_CAMERAS
#define DJROXZHIA_CAMERAS

#include "glm/glm/glm.hpp"

namespace DJROXZHIA {

	class OrthographicCamera
	{
	public:
		OrthographicCamera(const float& left, const float& right, const float& bottom, const float& top, const float& near_plane, const float& far_plane);

		inline glm::vec3 GetPosition() { return m_position; }
		inline void SetPosition(const glm::vec3& position) { m_position = position;	}

		inline float GetRotation() { return m_rotation; }
		inline void SetRotation(const float rotation) { m_rotation = rotation; }

		inline glm::mat4 GetProjectionMatrix() { return m_projectionMatrix; }
		inline void SetProjectionMatrix(const glm::mat4& projection_matrix) { m_projectionMatrix = projection_matrix; }

		inline glm::mat4 GetViewMatrix() { return m_viewMatrix; }
		inline void SetViewMatrix(const glm::mat4& viewMatrix) { m_viewMatrix = viewMatrix; }

		void UpdateProjectionMatrix(const float& left, const float& right, const float& bottom, const float& top, const float& near_plane, const float& far_plane);
		void UpdateViewMatrix();

	private:
		glm::vec3 m_position;
		float m_rotation = 0.0f;

		glm::mat4 m_projectionMatrix;
		glm::mat4 m_viewMatrix;

	};

}

#endif // !DJROXZHIA_CAMERAS
