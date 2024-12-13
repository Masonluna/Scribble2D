#pragma once
#include "Renderer/IBufferVertex.h"
#include "glad/glad.h"

namespace Scribble {

	class OpenGLVertexBuffer : public IBufferVertex
	{
	public:
		OpenGLVertexBuffer(uint32_t size);
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		~OpenGLVertexBuffer();

		void setData(const void* data, uint32_t size) override;


		void Bind() const override { glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); }
		void Unbind() const override { glBindBuffer(GL_ARRAY_BUFFER, 0); }
		const VertexBufferLayout& GetLayout() const override { return m_Layout; }
		void SetLayout(const VertexBufferLayout& layout) override { m_Layout = layout; }

	private:
		unsigned int m_RendererID;
		VertexBufferLayout m_Layout;
	};
}