#pragma once
#include "VertexBufferLayout.h"
#include "glad/glad.h"

namespace Scribble {

	class VertexBuffer
	{
	public:
		VertexBuffer() = default;
		VertexBuffer(uint32_t size);
		VertexBuffer(float* vertices, uint32_t size);
		~VertexBuffer();

		void setData(const void* data, uint32_t size);


		void Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); }
		void Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
		const VertexBufferLayout& GetLayout() const { return m_Layout; }
		void SetLayout(const VertexBufferLayout& layout) { m_Layout = layout; }

	private:
		unsigned int m_RendererID = 0;
		VertexBufferLayout m_Layout;
	};
}