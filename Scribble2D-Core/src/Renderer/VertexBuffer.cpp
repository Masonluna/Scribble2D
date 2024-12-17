#include "scbpch.h"
#include "VertexBuffer.h"

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
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		SCB_CORE_INFO("OpenGL Error before glGenBuffers: {0}",error);
	}
}

Scribble::VertexBuffer::~VertexBuffer()
{
	SCB_CORE_INFO("Vertex Buffer Destructor Called!\n  Renderer ID: {0}", m_RendererID);
	if (m_RendererID != 0)
		glDeleteBuffers(1, &m_RendererID);
}