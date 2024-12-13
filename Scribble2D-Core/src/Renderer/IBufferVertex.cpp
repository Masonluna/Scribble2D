#include "scbpch.h"
#include "IBufferVertex.h"
#include "Platform/OpenGL/OpenGLVertexBuffer.h"

namespace Scribble {

	// For now, only OpenGl is supported.
	std::shared_ptr<IBufferVertex> IBufferVertex::Create(uint32_t size)
	{
		return std::make_shared<OpenGLVertexBuffer>(size);
	}

	std::shared_ptr<IBufferVertex> IBufferVertex::Create(float* vertices, uint32_t size)
	{
		return std::make_shared<OpenGLVertexBuffer>(vertices, size);
	}

}