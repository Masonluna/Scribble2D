#pragma once
#include "Renderer/IVertexArray.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"
#include "Platform/OpenGL/OpenGLVertexBuffer.h"


namespace Scribble {

	class OpenGLVertexArray : public IVertexArray
	{
	public:


		//void AddVertexBuffer(const std::shared_ptr<IBufferVertex>& vertexBuffer) override { m_VertexBuffers.push_back(vertexBuffer); }


		//const std::vector<std::shared_ptr<IBufferVertex>>& GetVertexBuffers() const override { return m_VertexBuffers; }

		const std::shared_ptr<IBufferIndex>& GetIndexBuffer() const override { return m_IndexBuffer; }
	private:
		std::vector<std::shared_ptr<OpenGLVertexBuffer>>& m_VertexBuffers;
		std::shared_ptr<OpenGLIndexBuffer>& m_IndexBuffer;
	};

}