#pragma once
#include "scbpch.h"
#include "IBufferVertex.h"
#include "IBufferIndex.h"

namespace Scribble {

	enum class Shapes
	{
		None = 0, 
		Triangle = 1,
		Quad = 2
	};
		

	// TODO: Create coordinate systems for each shape type
	namespace Coords {


		float triangleVertices[] = {
			// Position		// Texture
			0.5f, 0.0f,		0.5f, 0.0f,
			0.0f, 1.0f,		0.0f, 1.0f,
			1.0f, 1.0f,		1.0f, 1.0f
		};


		float quadVertices[] = {
			// Position		// Texture
			0.0f, 0.0f,		0.0f, 0.0f,
			1.0f, 0.0f,		1.0f, 0.0f,
			0.0f, 1.0f,		0.0f, 1.0f,
			1.0f, 1.0f,		1.0f, 1.0f
		};

	}


	class IVertexArray
	{
	public:
		virtual ~IVertexArray() = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const std::shared_ptr<IBufferVertex>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IBufferIndex>& indexBuffer) = 0;

		virtual const std::vector<std::shared_ptr<IBufferVertex>>& GetVertexBuffers() const = 0;
		virtual const std::shared_ptr<IBufferIndex>& GetIndexBuffer() const = 0;

		static std::shared_ptr<IVertexArray> Create();
	};

}