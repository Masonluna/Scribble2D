#include "scbpch.h"
#include "Scribble2D/Renderer/IndexBuffer.h"

Scribble::IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t count)
	: m_Count(count)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);

	for (int i = 0; i < count; i++) {
		SCB_TRACE("Index {0}: {1}", i, indices[i]);
	}

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}
