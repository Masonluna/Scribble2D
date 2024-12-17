#pragma once
#include "VertexArray.h"
#include "Shader.h"
#include "glad/glad.h"

#include <unordered_map>

namespace Scribble {
	
	// TODO: Create coordinate systems for each shape type
	struct VertexData
	{

		float triangleVertices[12] = {
			// Position		// Texture
			0.5f, 0.0f,		0.5f, 0.0f,
			0.0f, 1.0f,		0.0f, 1.0f,
			1.0f, 1.0f,		1.0f, 1.0f
		};


		float quadVertices[16] = {
			// Position		// Texture
			0.0f, 0.0f,		0.0f, 0.0f,
			1.0f, 0.0f,		1.0f, 0.0f,
			0.0f, 1.0f,		0.0f, 1.0f,
			1.0f, 1.0f,		1.0f, 1.0f
		};


		uint32_t quadIndices[6] = {
			0, 1, 2,
			1, 2, 3
		};

	};


	enum class Shapes
	{
		None = 0,
		Triangle = 1,
		Quad = 2
	};


	class Renderer
	{

	public:
		Renderer() = default;
		void Init();

		void SetClearColor(const glm::vec4& color) { glClearColor(color.r, color.g, color.b, color.a); };
		void Clear();

		void DrawQuad(const glm::vec2& pos, const glm::vec2& size, float rotate, const glm::vec4& color);
		//void DrawQuad(glm::vec2& pos, float width, float height, float rotate = 0.0f, Texture2D& texture);
		void DrawTriangle(const glm::vec2& pos, float scale, float rotate, const glm::vec4& color);

		void DrawLine(const glm::vec2& p1, const glm::vec2& p2, const glm::vec4& color, float thickness);

		void DrawString(const std::string& text, const glm::vec2& pos, float scale, const glm::vec4& color);

	private:
		Shader m_TexturedShader;
		Shader m_SolidShader;
		VertexArray m_VertexArray;
		VertexData m_VertexData;
		// Unordered Map is not guaranteed to be useful here. But in the event I add more polygons, I want to future proof this class.
		std::unordered_map<Shapes, VertexBuffer> m_VertexBuffers;
		std::unordered_map<Shapes, IndexBuffer> m_IndexBuffers;
	};

}
