#include "scbpch.h"
#include "Scribble2D/Renderer/Renderer.h"
#include "Scribble2D/Renderer/ResourceManager.h"

#include "glm-1.0.1/glm/gtc/matrix_transform.hpp"
namespace Scribble {


	void Renderer::Init()
	{

		// ======== Initialize Render Data ========
		// ========================================
		m_VertexArray.Init();

		uint32_t quadIndices[6] = {
			0, 1, 2,
			1, 2, 3
		};

		m_VertexBuffers.emplace(std::piecewise_construct,
			std::forward_as_tuple(Shapes::Triangle),
			std::forward_as_tuple(m_VertexData.triangleVertices, sizeof(VertexData::triangleVertices)));

		m_VertexBuffers.emplace(std::piecewise_construct,
			std::forward_as_tuple(Shapes::Quad),
			std::forward_as_tuple(m_VertexData.quadVertices, sizeof(VertexData::quadVertices)));


		// Index Buffers 
		m_IndexBuffers.emplace(std::piecewise_construct,
			std::forward_as_tuple(Shapes::Quad),
			std::forward_as_tuple(quadIndices, 6));


		// Set Vertex Buffer Layout
		VertexBufferLayout layout = {
			{Scribble::ShaderDataType::Float2, "a_Position"},
			{Scribble::ShaderDataType::Float2, "a_TexCoords"}
		};

		m_VertexBuffers[Shapes::Quad].SetLayout(layout);


		// ======== Initialize Shaders ============
		// ========================================
		m_SolidShader =    ResourceManager::GetShader("solidShader");
		m_TexturedShader = ResourceManager::GetShader("textureShader");

		m_TextShader = ResourceManager::GetShader("textShader");

		// ======== Initialize Textures ===========
		// ========================================

	}

	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::DrawQuad(const glm::vec2& pos, const glm::vec2& size, float rotate, const glm::vec3& color)
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
		// Projection can probably go into Framebuffer somewhere.
		this->m_SolidShader.Bind();
		glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(Application::Get().GetWindow().GetWidth()),
			static_cast<float>(Application::Get().GetWindow().GetHeight()), 0.0f, -1.0f, 1.0f);
		m_SolidShader.SetMat4("projection", projection);

		m_VertexArray.AddBuffer(m_VertexBuffers[Shapes::Quad], m_VertexBuffers[Shapes::Quad].GetLayout());

		m_SolidShader.SetMat4("model", model);
		m_SolidShader.SetFloat4("spriteColor", glm::vec4(color, 1.0f));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	void Renderer::DrawQuad(const glm::vec2& pos, float width, float height, float rotate, Texture2D& texture)
	{
		m_VertexArray.Bind();  // Bind VAO

		m_VertexBuffers[Shapes::Quad].Bind();  // Bind VBO
		m_IndexBuffers[Shapes::Quad].Bind();   // Bind EBO

		// Go in REVERSE ORDER: Transform, then rotate, then scale
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(pos, 0.0f)); // Transform 

		model = glm::translate(model, glm::vec3(0.5f * width, 0.5f * height, 0.0f)); // Origin now in center for rotation
		model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate
		model = glm::translate(model, glm::vec3(-0.5f * width, -0.5f * height, 0.0f)); // Origin back

		model = glm::scale(model, glm::vec3(width, height, 1.0f)); // Scale


		// TODO: this can most certainly be done somewhere else, and outside of the render loop.
		// Projection can probably go into Framebuffer somewhere.
		this->m_TexturedShader.Bind();
		glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(Application::Get().GetWindow().GetWidth()),
			static_cast<float>(Application::Get().GetWindow().GetHeight()), 0.0f, -1.0f, 1.0f);
		m_TexturedShader.SetMat4("projection", projection);

		m_VertexArray.AddBuffer(m_VertexBuffers[Shapes::Quad], m_VertexBuffers[Shapes::Quad].GetLayout());

		m_TexturedShader.SetMat4("model", model);
		m_TexturedShader.SetFloat3("spriteColor", glm::vec3(1.0f));
		texture.Bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	void Renderer::DrawObject(const Object& object)
	{
		DrawQuad(object.GetPosition(), object.GetSize(), object.GetRotation(), object.GetColor());
	}

	void Renderer::DrawTriangle(const glm::vec2& pos, float scale, float rotate, const glm::vec3& color)
	{}

	void Renderer::DrawLine(const glm::vec2 & p1, const glm::vec2 & p2, const glm::vec4 & color, float thickness)
	{

	}

	void Renderer::DrawString(const std::string & text, const glm::vec2 & pos, float scale, const glm::vec4 & color)
	{

	}

}