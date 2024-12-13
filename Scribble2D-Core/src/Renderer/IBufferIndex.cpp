#include "scbpch.h"
#include "IBufferIndex.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"

namespace Scribble {


	/*
	* TODO: Create a RendererAPI to easily swap between Graphics frameworks.
	*/
	// Only OpenGLIndexBuffers are supported Currently
	std::shared_ptr<IBufferIndex> IBufferIndex::Create(uint32_t* indices, uint32_t count)
	{
		return std::make_shared<OpenGLIndexBuffer>(indices, count);
	}

}