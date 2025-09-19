#include "Shader.h"

namespace DJROXZHIA {

	Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
		: m_vertexShaderPath(vertexShaderPath), m_fragmentShaderPath(fragmentShaderPath)
	{
		if (!LoadShader())
		{
			std::cerr << "ERROR::SHADER NOT LOADED!\n";
		}
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_shaderID);
	}

	void Shader::Enable() const
	{
		glUseProgram(m_shaderID);
	}

	void Shader::Disable() const
	{
		glUseProgram(0);
	}

	void Shader::SetTextures(const char* name)
	{
		GLint textures[16];
		for (int i = 0; i < 16; i++)
		{
			textures[i] = i;
		}
		GLint location = glGetUniformLocation(m_shaderID, name);
		glUniform1iv(location, 16, textures);
	}

	void Shader::SetUniformMat4(const char* name, const glm::mat4& matrix) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_shaderID, name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Shader::SetUniformVec4(const char* name, const glm::vec4& vector) const
	{
		glUniform4fv(glGetUniformLocation(m_shaderID, name), 1, glm::value_ptr(vector));
	}

	void Shader::SetUniformVec3(const char* name, const glm::vec3& vector) const
	{
		glUniform3fv(glGetUniformLocation(m_shaderID, name), 1, glm::value_ptr(vector));
	}

	void Shader::SetUniformVec2(const char* name, const glm::vec2& vector) const
	{
		glUniform2fv(glGetUniformLocation(m_shaderID, name), 1, glm::value_ptr(vector));
	}

	void Shader::SetUniformInt(const char* name, const GLint& integer) const
	{
		glUniform1i(glGetUniformLocation(m_shaderID, name), integer);
	}

	void Shader::SetUniformFloat(const char* name, const GLfloat& decimal_num) const
	{
		glUniform1f(glGetUniformLocation(m_shaderID, name), decimal_num);
	}

	void Shader::SetUniformBool(const char* name, const GLboolean& value) const
	{
		glUniform1i(glGetUniformLocation(m_shaderID, name), (int)value);
	}

	void Shader::SetUniformMat4Pointer(const char* name, glm::mat4* matrix, uint32_t size) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_shaderID, name), size, GL_FALSE, glm::value_ptr(matrix[0]));
	}

	void Shader::SetUniformVec4Pointer(const char* name, glm::vec4* vector, uint32_t size) const
	{
		glUniform4fv(glGetUniformLocation(m_shaderID, name), size, glm::value_ptr(vector[0]));
	}

	void Shader::SetUniformVec3Pointer(const char* name, glm::vec3* vector, uint32_t size) const
	{
		glUniform3fv(glGetUniformLocation(m_shaderID, name), 1, glm::value_ptr(vector[0]));
	}

	void Shader::SetUniformVec2Pointer(const char* name, glm::vec2* vector, uint32_t size) const
	{
		glUniform2fv(glGetUniformLocation(m_shaderID, name), 1, glm::value_ptr(vector[0]));
	}

	void Shader::SetUniformIntPointer(const char* name, GLint* integer, uint32_t size) const
	{
		glUniform1iv(glGetUniformLocation(m_shaderID, name), size, integer);
	}

	void Shader::SetUniformFloatPointer(const char* name, GLfloat* decimal_num, uint32_t size) const
	{
		glUniform1fv(glGetUniformLocation(m_shaderID, name), size, decimal_num);
	}

	void Shader::SetUniformBoolPointer(const char* name, GLboolean* value, uint32_t size) const
	{
		glUniform1iv(glGetUniformLocation(m_shaderID, name), size, (int*)value);
	}

	bool Shader::LoadShader()
	{
		m_shaderID = glCreateProgram();
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		std::string vertexShaderSourceString = DJROXZHIA::FileUtils::ReadFile(m_vertexShaderPath);
		std::string fragmentShaderSourceString = DJROXZHIA::FileUtils::ReadFile(m_fragmentShaderPath);

		const char* vertexShaderSourceChar = vertexShaderSourceString.c_str();
		const char* fragmentShaderSourceChar = fragmentShaderSourceString.c_str();


		glShaderSource(vertexShader, 1, &vertexShaderSourceChar, NULL);
		glCompileShader(vertexShader);

		GLint result;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(vertexShader, length, &length, &error[0]);
			std::cout << "ERROR::SHADER::VERTEX::" << &error[0] << "\n";
			glDeleteShader(vertexShader);
		}


		glShaderSource(fragmentShader, 1, &fragmentShaderSourceChar, NULL);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(fragmentShader, length, &length, &error[0]);
			std::cout << "ERROR::SHADER::FRAGMENT::" << &error[0] << "\n";
			glDeleteShader(fragmentShader);
		}


		glAttachShader(m_shaderID, vertexShader);
		glAttachShader(m_shaderID, fragmentShader);

		glLinkProgram(m_shaderID);

		glGetProgramiv(m_shaderID, GL_LINK_STATUS, &result);
		if (!result)
		{
			char error[512];
			glGetProgramInfoLog(m_shaderID, 512, NULL, error);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << error << "\n";
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return true;
	}

}