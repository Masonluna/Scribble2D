#include "scbpch.h"
#include "OpenGLRenderer2D.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Scribble {



	void OpenGLRenderer2D::Init()
	{

		// ======== Initialize Render Data ========
		// ========================================
		m_VertexArray = OpenGLVertexArray();


		// Vertex Buffers
		m_VertexBuffers[Shapes::Triangle] = OpenGLVertexBuffer(Coords::triangleVertices, sizeof(Coords::triangleVertices));
		m_VertexBuffers[Shapes::Quad] = OpenGLVertexBuffer(Coords::quadVertices, sizeof(Coords::quadVertices));

		// Index Buffers 
		m_IndexBuffers[Shapes::Quad] = OpenGLIndexBuffer(Coords::quadIndices, sizeof(Coords::quadIndices));




	}

	void OpenGLRenderer2D::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRenderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, float rotate, const glm::vec4& color)
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

	void OpenGLRenderer2D::DrawTriangle(const glm::vec2& pos, float scale, float rotate, const glm::vec4& color)
	{}

	void OpenGLRenderer2D::DrawLine(const glm::vec2 & p1, const glm::vec2 & p2, const glm::vec4 & color, float thickness)
	{

	}

	void OpenGLRenderer2D::DrawString(const std::string & text, const glm::vec2 & pos, float scale, const glm::vec4 & color)
	{

	}

}