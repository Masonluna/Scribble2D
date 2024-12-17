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

		m_VertexBuffers.emplace(std::piecewise_construct,
			std::forward_as_tuple(Shapes::Triangle),
			std::forward_as_tuple(m_VertexData.triangleVertices, sizeof(VertexData::triangleVertices)));

		m_VertexBuffers.emplace(std::piecewise_construct,
			std::forward_as_tuple(Shapes::Quad),
			std::forward_as_tuple(m_VertexData.quadVertices, sizeof(VertexData::quadVertices)));


		// Index Buffers 
		m_IndexBuffers.emplace(std::piecewise_construct,
			std::forward_as_tuple(Shapes::Quad),
			std::forward_as_tuple(m_VertexData.quadIndices, 6));


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
		m_VertexArray.Bind();  // Bind VAO

		m_VertexBuffers[Shapes::Quad].Bind();  // Bind VBO
		m_IndexBuffers[Shapes::Quad].Bind();   // Bind EBO

		// Go in REVERSE ORDER: Transform, then rotate, then scale
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(pos, 0.0f)); // Transform 

		model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // Origin now in center for rotation
		model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate
		model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Origin back

		model = glm::scale(model, glm::vec3(size, 1.0f)); // Scale


		// TODO: this can most certainly be done somewhere else, and outside of the render loop.
		glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(1920),
			static_cast<float>(1080), 0.0f, -1.0f, 1.0f);
		m_SolidShader.SetMat4("projection", projection);

		this->m_SolidShader.Bind();
		m_VertexArray.AddBuffer(m_VertexBuffers[Shapes::Quad], m_VertexBuffers[Shapes::Quad].GetLayout());

		m_SolidShader.SetMat4("model", model);
		m_SolidShader.SetFloat4("spriteColor", color);

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