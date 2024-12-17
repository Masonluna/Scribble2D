#include "scbpch.h"
#include "IndexBuffer.h"

Scribble::IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t count)
	: m_Count(count)
{
	SCB_CORE_INFO("glGenBuffers Called [IndexBuffer]");

	glGenBuffers(1, &m_RendererID);

	// GL_ELEMENT_ARRAY_BUFFER is invalid without a bound VAO
	// Using GL_ARRAY_BUFFER will work regardless of VAO state
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}
