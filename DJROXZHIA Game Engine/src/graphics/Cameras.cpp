#include "Cameras.h"
#include <glm/glm/ext/matrix_clip_space.hpp>
#include <glm/glm/ext/matrix_transform.hpp>

namespace DJROXZHIA {

	OrthographicCamera::OrthographicCamera(const float& left, const float& right, const float& bottom, const float& top, const float& near_plane, const float& far_plane)
		: m_position(glm::vec3(0.0f))
	{
		m_projectionMatrix = glm::ortho(left, right, bottom, top, near_plane, far_plane);

		glm::vec3 camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
		m_viewMatrix = glm::mat4(1.0f);
		m_viewMatrix = glm::lookAt(m_position, camera_front + m_position, camera_up);
	}

	void OrthographicCamera::UpdateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 1.0f));

		m_viewMatrix = glm::inverse(transform);
	}

	void OrthographicCamera::UpdateProjectionMatrix(const float& left, const float& right, const float& bottom, const float& top, const float& near_plane, const float& far_plane)
	{
		m_projectionMatrix = glm::ortho(left, right, bottom, top, near_plane, far_plane);
	}
}