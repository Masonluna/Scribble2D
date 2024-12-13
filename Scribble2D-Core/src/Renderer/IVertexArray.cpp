#include "scbpch.h"
#include "IVertexArray.h"
#include <Platform/OpenGL/OpenGLVertexArray.h>

std::shared_ptr<Scribble::IVertexArray> Scribble::IVertexArray::Create()
{
	return std::make_shared<Scribble::OpenGLVertexArray>();
}
