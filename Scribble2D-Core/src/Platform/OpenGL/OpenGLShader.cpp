#include "scbpch.h"
#include "OpenGLShader.h"

namespace Scribble {

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		this->Bind();
		glUniform1i(glGetUniformLocation(this->m_ShaderID, name.c_str()), value);
	}

	void OpenGLShader::SetIntArray(const std::string& name, int* values, uint32_t count)
	{
		this->Bind();
		glUniform1iv(glGetUniformLocation(this->m_ShaderID, name.c_str()), count, values);
	}

	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		this->Bind();
		glUniform1f(glGetUniformLocation(this->m_ShaderID, name.c_str()), value);
	}

	void OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& value)
	{
		this->Bind();
		glUniform2f(glGetUniformLocation(this->m_ShaderID, name.c_str()), value.x, value.y);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		this->Bind();
		glUniform3f(glGetUniformLocation(this->m_ShaderID, name.c_str()), value.x, value.y, value.z);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		this->Bind();
		glUniform4f(glGetUniformLocation(this->m_ShaderID, name.c_str()), value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		this->Bind();
		glUniformMatrix4fv(glGetUniformLocation(this->m_ShaderID, name.c_str()), 1, false, glm::value_ptr(value));
	}

	void OpenGLShader::Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource)
	{
		uint32_t sVertex, sFragment, gShader;

		sVertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(sVertex, 1, &vertexSource, NULL);
		glCompileShader(sVertex);
		checkCompileErrors(sVertex, "VERTEX");

		sFragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(sFragment, 1, &fragmentSource, NULL);
		glCompileShader(sFragment);
		checkCompileErrors(sFragment, "FRAGMENT");

		if (geometrySource != nullptr)
		{
			gShader = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(gShader, 1, &geometrySource, NULL);
			glCompileShader(gShader);
			checkCompileErrors(gShader, "GEOMETRY");
		}

		this->m_ShaderID = glCreateProgram();
		glAttachShader(this->m_ShaderID, sVertex);
		glAttachShader(this->m_ShaderID, sFragment);
		if (geometrySource != nullptr)
			glAttachShader(this->m_ShaderID, gShader);
		glLinkProgram(this->m_ShaderID);
		checkCompileErrors(this->m_ShaderID, "PROGRAM");

		glDeleteShader(sVertex);
		glDeleteShader(sFragment);
		if (geometrySource != nullptr)
			glDeleteShader(gShader);
	}

	void OpenGLShader::checkCompileErrors(uint32_t object, std::string type)
	{
		int success;
		char infoLog[1024];
		if (type != "PROGRAM") {
			glGetShaderiv(object, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(object, 1024, NULL, infoLog);
				SCB_CORE_ERROR("[Shader] Compile-time error: Type {0}\n{1}", type, infoLog);
			}
		}
		else {
			glGetProgramiv(object, GL_LINK_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(object, 1024, NULL, infoLog);
				SCB_CORE_ERROR("[Shader] Compile-time error: Type {0}\n{1}", type, infoLog);
			}
		}
	}

}