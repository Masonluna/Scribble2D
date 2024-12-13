#pragma once

#include "Renderer/Shader.h"
#include "glm/gtc/type_ptr.hpp"
#include "glad/glad.h"

namespace Scribble {

	class OpenGLShader : public Shader
	{
	public:
		uint32_t m_ShaderID = 0;
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
		void SetMat4(const std::string& name, const glm::mat4& value) override;


		void Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr);

	private:
		void checkCompileErrors(uint32_t object, std::string type);
	};

}

