#include "scbpch.h"
#include "OpenGLRenderer2D.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Scribble {



	void OpenGLRenderer2D::Init()
	{

	}

	void OpenGLRenderer2D::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRenderer2D::DrawQuad(glm::vec2& pos, float width, float height, float rotate, const glm::vec4& color)
	{
		//this->m_Shader.Use();
		// Transformation order: scale, rotation, reverse
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(pos, 0.0f)); // Scale

		model = glm::translate(model, glm::vec3(0.5f * width, 0.5f * height, 0.0f)); // Origin now in center for rotation
		model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate
		model = glm::translate(model, glm::vec3(-0.5f * width, -0.5f * height, 0.0f)); // Origin back

		model = glm::scale(model, glm::vec3(width, height, 1.0f));


	}

	void OpenGLRenderer2D::DrawLine(glm::vec2 & p1, glm::vec2 & p2, const glm::vec4 & color, float thickness)
	{

	}

	void OpenGLRenderer2D::DrawString(const std::string & text, glm::vec2 & pos, float scale, const glm::vec4 & color)
	{

	}

}