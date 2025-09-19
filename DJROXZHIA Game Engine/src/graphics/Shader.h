#ifndef DJROXZHIA_SHADER
#define DJROXZHIA_SHADER

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include <iostream>

#include "utils/FileUtils.h"

namespace DJROXZHIA {

	class Shader
	{
	public:
		Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
		~Shader();

		void Enable() const;
		void Disable() const;

		void SetTextures(const char* name);

		void SetUniformMat4(const char* name, const glm::mat4& matrix) const;
		void SetUniformVec4(const char* name, const glm::vec4& vector) const;
		void SetUniformVec3(const char* name, const glm::vec3& vector) const;
		void SetUniformVec2(const char* name, const glm::vec2& vector) const;
		void SetUniformInt(const char* name, const GLint& integer) const;
		void SetUniformFloat(const char* name, const GLfloat& decimal_num) const;
		void SetUniformBool(const char* name, const GLboolean& value) const;

		void SetUniformMat4Pointer(const char* name, glm::mat4* matrix, uint32_t size) const;
		void SetUniformVec4Pointer(const char* name, glm::vec4* vector, uint32_t size) const;
		void SetUniformVec3Pointer(const char* name, glm::vec3* vector, uint32_t size) const;
		void SetUniformVec2Pointer(const char* name, glm::vec2* vector, uint32_t size) const;
		void SetUniformIntPointer(const char* name, GLint* integer, uint32_t size) const;
		void SetUniformFloatPointer(const char* name, GLfloat* decimal_num, uint32_t size) const;
		void SetUniformBoolPointer(const char* name, GLboolean* value, uint32_t size) const;

		inline const GLuint& GetID() { return m_shaderID; }

	private:
		GLuint m_shaderID;
		const char* m_vertexShaderPath, * m_fragmentShaderPath;

	private:
		bool LoadShader();
	};

}

#endif // !DJROXZHIA_SHADER

