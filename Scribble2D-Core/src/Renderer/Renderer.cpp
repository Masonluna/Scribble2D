#include "scbpch.h"
#include "Renderer.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Scribble {



	void Renderer::Init()
	{

		// ======== Initialize Render Data ========
		// ========================================
		m_VertexArray = VertexArray();


		// Vertex Buffers
		m_VertexBuffers[Shapes::Triangle] = VertexBuffer(VertexData::triangleVertices, sizeof(VertexData::triangleVertices));
		m_VertexBuffers[Shapes::Quad] = VertexBuffer(VertexData::quadVertices, sizeof(VertexData::quadVertices));

		// Index Buffers 
		m_IndexBuffers[Shapes::Quad] = IndexBuffer(VertexData::quadIndices, sizeof(VertexData::quadIndices));

		// Set Vertex Buffer Layout
		VertexBufferLayout layout = {
			{Scribble::ShaderDataType::Float2, "a_Position"},
			{Scribble::ShaderDataType::Float2, "a_TexCoords"}
		};

		m_VertexBuffers[Shapes::Quad].SetLayout(layout);


	}

	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::DrawQuad(const glm::vec2& pos, const glm::vec2& size, float rotate, const glm::vec4& color)
	{
		//this->m_Shader.Use();
		// Go in REVERSE ORDER: Transform, then rotate, then scale
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(pos, 0.0f)); // Transform 

		model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // Origin now in center for rotation
		model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate
		model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Origin back

		model = glm::scale(model, glm::vec3(size, 1.0f)); // Scale

		m_VertexArray.AddBuffer(m_VertexBuffers[Shapes::Quad], m_VertexBuffers[Shapes::Quad].GetLayout());
		m_IndexBuffers[Shapes::Quad].Bind();

		m_SolidShader.SetMat4("model", model);
		m_SolidShader.SetFloat3("spriteColor", color);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	void Renderer::DrawTriangle(const glm::vec2& pos, float scale, float rotate, const glm::vec4& color)
	{}

	void Renderer::DrawLine(const glm::vec2 & p1, const glm::vec2 & p2, const glm::vec4 & color, float thickness)
	{

	}

	void Renderer::DrawString(const std::string & text, const glm::vec2 & pos, float scale, const glm::vec4 & color)
	{

	}

}