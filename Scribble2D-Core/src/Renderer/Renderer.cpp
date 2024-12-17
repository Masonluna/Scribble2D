#include "scbpch.h"
#include "Renderer.h"
#include "ResourceManager.h"

#include "glm/gtc/matrix_transform.hpp"
namespace Scribble {


	void Renderer::Init()
	{

		// ======== Initialize Render Data ========
		// ========================================
		m_VertexArray.Init();

		// Vertex Buffers
		m_VertexBuffers.emplace(Shapes::Triangle, VertexBuffer(m_VertexData.triangleVertices, sizeof(VertexData::triangleVertices)));

		// TODO: Figure out why it's reusing 1 as a renderer ID.
		m_VertexBuffers.emplace(Shapes::Quad, VertexBuffer(m_VertexData.quadVertices, sizeof(VertexData::quadVertices)));

		// Index Buffers 
		m_IndexBuffers.emplace(Shapes::Quad, IndexBuffer(m_VertexData.quadIndices, sizeof(VertexData::quadIndices)));
		m_VertexBuffers[Shapes::Quad].Bind();
		GLint vboSize = 0;
		glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &vboSize);
		SCB_CORE_INFO("Vertex Buffer Size: {0} bytes", vboSize);

		// Set Vertex Buffer Layout
		VertexBufferLayout layout = {
			{Scribble::ShaderDataType::Float2, "a_Position"},
			{Scribble::ShaderDataType::Float2, "a_TexCoords"}
		};

		m_VertexBuffers[Shapes::Quad].SetLayout(layout);

		// ======== Initialize Shaders ============
		// ========================================
		ResourceManager::InitializeShaders();
		m_SolidShader =    ResourceManager::GetShader("solidShader");
		m_TexturedShader = ResourceManager::GetShader("texShader");
	}

	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::DrawQuad(const glm::vec2& pos, const glm::vec2& size, float rotate, const glm::vec4& color)
	{

		// Go in REVERSE ORDER: Transform, then rotate, then scale
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(pos, 0.0f)); // Transform 

		model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // Origin now in center for rotation
		model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate
		model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Origin back

		model = glm::scale(model, glm::vec3(size, 1.0f)); // Scale

		this->m_SolidShader.Bind();
		m_VertexArray.AddBuffer(m_VertexBuffers[Shapes::Quad], m_VertexBuffers[Shapes::Quad].GetLayout());
		m_VertexBuffers[Shapes::Quad].Bind();
		m_IndexBuffers[Shapes::Quad].Bind();

		m_SolidShader.SetMat4("model", model);
		m_SolidShader.SetFloat4("spriteColor", color);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			SCB_CORE_ERROR("OpenGL Error: {0}", error);
		}

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