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
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;


		// Quads and Lines
		virtual void DrawQuad(const glm::vec2& pos, float width, float height, float rotate, const glm::vec4& color) = 0;
		//virtual void DrawQuad(glm::vec2& pos, float width, float height, float rotate = 0.0f, Texture2D& texture) = 0;

		virtual void DrawLine(const glm::vec2& p1, const glm::vec2& p2, const glm::vec4& color, float thickness) = 0;

		virtual void DrawString(const std::string& text, const glm::vec2& pos, float scale, const glm::vec4& color) = 0;

		// Batch Rendering
		//virtual void BeginBatch() = 0;
		//virtual void EndBatch() = 0;
		//virtual void Flush() = 0;
	};

}