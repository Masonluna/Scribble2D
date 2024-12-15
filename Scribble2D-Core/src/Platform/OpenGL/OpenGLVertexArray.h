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

		void AddBuffer(const OpenGLVertexBuffer& vb, const VertexBufferLayout& layout);


	private:
		uint32_t m_RendererID;
	};

}