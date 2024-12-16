#pragma once
#include "glad/glad.h"

namespace Scribble {

	class IndexBuffer
	{
	public:
		IndexBuffer() = default;
		IndexBuffer(uint32_t* indices, uint32_t count);

		~IndexBuffer()
		{
			glDeleteBuffers(1, &m_RendererID);
		}

		void Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID); }
		void Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

		const uint32_t GetCount() const { return m_Count; }

	private:
		unsigned int m_RendererID;
		uint32_t m_Count;
	};
}