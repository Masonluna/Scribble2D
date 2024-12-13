#pragma once
#include <cstdint>
#include "VertexBufferLayout.h"


namespace Scribble {

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer();

		virtual void Bind();
		virtual void Unbind();

		virtual void setData(const void* data, uint32_t count);
		virtual const VertexBufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const VertexBufferLayout& layout) = 0;

		static std::shared_ptr<VertexBuffer> Create(uint32_t size);
		static std::shared_ptr<VertexBuffer> Create(float* vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;
		
		static std::shared_ptr<IndexBuffer> Create(uint32_t* indices, uint32_t count);
	};

}