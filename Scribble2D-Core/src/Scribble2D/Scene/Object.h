#pragma once

#include "glm/glm.hpp"

namespace Scribble {

	class Object
	{
	public:
		Object() {}
		//Object(Texture2D texture);
		//Object(glm::vec4& color);
		Object(glm::vec2& position, glm::vec2& size, float rotation, glm::vec3& color)
			: m_Position(position), m_Size(size), m_Rotation(rotation), m_Color(color)
		{

		}
		//Object(glm::vec2& positon, glm::vec2& size, float rotation, Texture2D texture);


	protected:
		glm::vec2 m_Position;
		glm::vec2 m_Size;
		float m_Rotation;


		// Texture2D m_Texture;
		glm::vec3 m_Color;
	};

}