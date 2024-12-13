#pragma once
#include "Renderer/IVertexArray.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"
#include "Platform/OpenGL/OpenGLVertexBuffer.h"


namespace Scribble {

	class OpenGLVertexArray : public IVertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		void Bind() const override;
		void Unbind() const override;

		void AddVertexBuffer(const std::shared_ptr<IBufferVertex>& vertexBuffer) override;
		void SetIndexBuffer(const std::shared_ptr<IBufferIndex>& indexBuffer) override;

		const std::vector<std::shared_ptr<IBufferVertex>>& GetVertexBuffers() const override { return m_VertexBuffers; }
		const std::shared_ptr<IBufferIndex>& GetIndexBuffer() const override { return m_IndexBuffer; }
	private:
		uint32_t m_RendererID;
		uint32_t m_VertexBufferIndex = 0;
		std::vector<std::shared_ptr<IBufferVertex>> m_VertexBuffers;
		std::shared_ptr<IBufferIndex> m_IndexBuffer;
	};

}