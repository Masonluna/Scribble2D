#pragma once
#include "Renderer/IRenderable2D.h"
#include "glad/glad.h"

namespace Scribble {
	
	class OpenGLRenderer2D : public IRenderable2D
	{

	public:
		void Init();

		void SetClearColor(const glm::vec4& color) override { glClearColor(color.r, color.g, color.b, color.a); };
		void Clear() override;

		void DrawQuad(glm::vec2& pos, float width, float height, float rotate, const glm::vec4& color);
		//void DrawQuad(glm::vec2& pos, float width, float height, float rotate = 0.0f, Texture2D& texture) override;

		void DrawLine(glm::vec2& p1, glm::vec2& p2, const glm::vec4& color, float thickness) override;

		void DrawString(const std::string& text, glm::vec2& pos, float scale, const glm::vec4& color) override;

	private:
		//Shader m_Shader;
	};

}
