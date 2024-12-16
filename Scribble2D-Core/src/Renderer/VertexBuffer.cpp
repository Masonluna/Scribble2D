#include "scbpch.h"
#include "VertexBuffer.h"

Scribble::VertexBuffer::VertexBuffer(uint32_t size)
{
	glCreateBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

Scribble::VertexBuffer::VertexBuffer(float* vertices, uint32_t size)
{
	glCreateBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

Scribble::VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(GL_ARRAY_BUFFER, 0);
}

void Scribble::VertexBuffer::setData(const void* data, uint32_t size)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}
