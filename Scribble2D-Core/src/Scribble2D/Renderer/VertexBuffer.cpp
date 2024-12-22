#include "scbpch.h"
#include "Scribble2D/Renderer/VertexBuffer.h"

Scribble::VertexBuffer::VertexBuffer(uint32_t size)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

Scribble::VertexBuffer::VertexBuffer(float* vertices, uint32_t size)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

Scribble::VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}