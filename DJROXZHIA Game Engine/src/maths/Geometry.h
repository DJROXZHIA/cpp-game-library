#ifndef DJROXZHIA_GEOMETRY
#define DJROXZHIA_GEOMETRY

#include <glm/glm/glm.hpp>
#include <glm/glm/ext/matrix_transform.hpp>

struct Vertex
{
	glm::mat4 transform = glm::mat4(1.0f);
	glm::vec3 translation = glm::vec3(0.0f);
	glm::vec3 scale = glm::vec3(0.0f);
	glm::vec3 rotation = glm::vec3(0.0f);
	float radians;

	Vertex(glm::vec3 _translation, glm::vec3 _scale, glm::vec3 _rotation, const float& _radians)
	{
		translation = _translation;
		scale = _scale;
		rotation = _rotation;
		radians = _radians;
		transform = glm::mat4(1.0f);
		transform = glm::translate(glm::mat4(1.0f), translation);
		//transform = glm::rotate(glm::mat4(1.0f), _radians, rotation);
		transform = glm::scale(transform, scale);
	}

	Vertex(){}

	void Translate(const glm::vec3& _translation)
	{
		translation = _translation;
		transform = glm::translate(transform, translation);
	}

	void Rotate(const float& _radians, const glm::vec3& _rotation)
	{
		rotation = _rotation;
		radians = _radians;
		transform = glm::rotate(transform, radians, _rotation);
	}

	void Scale(const glm::vec3& _scale)
	{
		scale = _scale;
		transform = glm::scale(transform, _scale);
	}

};

#endif // !DJROXZHIA_GEOMETRY