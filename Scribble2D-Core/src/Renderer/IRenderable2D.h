#pragma once
#include "scbpch.h"
#include "glm/glm.hpp"

namespace Scribble {

	class IRenderable2D
	{
	public:
		virtual ~IRenderable2D() = default;

		virtual void Init() = 0;


		// Clear
		virtual void SetClearColor(glm::vec4& color) = 0;
		virtual void Clear() = 0;


		// Quads and Lines
		virtual void DrawQuad(glm::vec2& pos, float width, float height, const glm::vec4& color) = 0;
		//virtual void DrawQuad(float x, float y, float width, float height, Texture2D texture) = 0;

		virtual void DrawLine(glm::vec2& p1, glm::vec2& p2, glm::vec4& color, float thickness) = 0;

		virtual void DrawText(const std::string& text, glm::vec2& pos, float scale, const glm::vec4& color) = 0;

		// Batch Rendering
		virtual void BeginBatch() = 0;
		virtual void EndBatch() = 0;
		virtual void Flush() = 0;
	};

}