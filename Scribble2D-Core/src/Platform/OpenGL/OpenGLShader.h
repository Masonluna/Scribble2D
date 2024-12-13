#pragma once

#include "Renderer/Shader.h"
#include "glad/glad.h"

namespace Scribble {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader() {}
		~OpenGLShader() = default;

		void Bind() const override { glUseProgram(m_ShaderID); }
		void Unbind() const override { glUseProgram(0); }

		void SetInt(const std::string& name, int value) override;
		void SetIntArray(const std::string& name, int* values, uint32_t count) override;
		void SetFloat(const std::string& name, float value) override;
		void SetFloat2(const std::string& name, const glm::vec2& value) override;
		void SetFloat3(const std::string& name, const glm::vec3& value) override;
		void SetFloat4(const std::string& name, const glm::vec4& value) override;


		void Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr);

	private:
		uint32_t m_ShaderID = 0;

		void checkCompileErrors(uint32_t object, std::string type);
	};

}

