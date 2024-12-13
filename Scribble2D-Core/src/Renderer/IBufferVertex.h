#pragma once
#include <cstdint>
#include "VertexBufferLayout.h"


namespace Scribble {

	class IBufferVertex
	{
	public:
		virtual ~IBufferVertex() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void setData(const void* data, uint32_t count) = 0;
		virtual const VertexBufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const VertexBufferLayout& layout) = 0;

		static std::shared_ptr<IBufferVertex> Create(uint32_t size);
		static std::shared_ptr<IBufferVertex> Create(float* vertices, uint32_t size);
	};
}