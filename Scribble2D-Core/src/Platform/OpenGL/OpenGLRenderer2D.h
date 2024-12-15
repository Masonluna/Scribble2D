#pragma once
#include "Renderer/IRenderable2D.h"
#include "OpenGLVertexArray.h"
#include "OpenGLShader.h"
#include "glad/glad.h"

#include <unordered_map>

namespace Scribble {
	
	// TODO: Create coordinate systems for each shape type
	namespace Coords {

		float triangleVertices[] = {
			// Position		// Texture
			0.5f, 0.0f,		0.5f, 0.0f,
			0.0f, 1.0f,		0.0f, 1.0f,
			1.0f, 1.0f,		1.0f, 1.0f
		};


		float quadVertices[] = {
			// Position		// Texture
			0.0f, 0.0f,		0.0f, 0.0f,
			1.0f, 0.0f,		1.0f, 0.0f,
			0.0f, 1.0f,		0.0f, 1.0f,
			1.0f, 1.0f,		1.0f, 1.0f
		};


		uint32_t quadIndices[] = {
			0, 1, 2,
			1, 2, 3
		};

	}

	class OpenGLRenderer2D : public IRenderable2D
	{

	public:
		void Init();

		void SetClearColor(const glm::vec4& color) override { glClearColor(color.r, color.g, color.b, color.a); };
		void Clear() override;

		void DrawQuad(const glm::vec2& pos, const glm::vec2& size, float rotate, const glm::vec4& color) override;
		//void DrawQuad(glm::vec2& pos, float width, float height, float rotate = 0.0f, Texture2D& texture) override;
		void DrawTriangle(const glm::vec2& pos, float scale, float rotate, const glm::vec4& color) override;

		void DrawLine(const glm::vec2& p1, const glm::vec2& p2, const glm::vec4& color, float thickness) override;

		void DrawString(const std::string& text, const glm::vec2& pos, float scale, const glm::vec4& color) override;

	private:
		OpenGLShader m_TexturedShader;
		OpenGLShader m_SolidShader;
		OpenGLVertexArray m_VertexArray;

		// Unordered Map is not guaranteed to be useful here. But in the event I add more polygons, I want to future proof this class.
		std::unordered_map<Shapes, OpenGLVertexBuffer> m_VertexBuffers;
		std::unordered_map<Shapes, OpenGLIndexBuffer> m_IndexBuffers;
	};

}
