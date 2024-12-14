#pragma once
#include "Renderer/IRenderable2D.h"
#include "OpenGLVertexArray.h"
#include "OpenGLShader.h"
#include "glad/glad.h"

#include <unordered_map>

namespace Scribble {
	
	class OpenGLRenderer2D : public IRenderable2D
	{

	public:
		void Init();

		void SetClearColor(const glm::vec4& color) override { glClearColor(color.r, color.g, color.b, color.a); };
		void Clear() override;

		void DrawQuad(const glm::vec2& pos, const glm::vec2& size, float rotate, const glm::vec4& color);
		//void DrawQuad(glm::vec2& pos, float width, float height, float rotate = 0.0f, Texture2D& texture) override;
		void DrawTriangle(const glm::vec2& pos, float scale, float rotate, const glm::vec4& color);

		void DrawLine(const glm::vec2& p1, const glm::vec2& p2, const glm::vec4& color, float thickness) override;

		void DrawString(const std::string& text, const glm::vec2& pos, float scale, const glm::vec4& color) override;

	private:
		OpenGLShader m_Shader;
		OpenGLVertexArray m_VertexArray;
	};

}
