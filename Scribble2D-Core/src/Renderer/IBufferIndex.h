#pragma once
#include "scbpch.h"
#include <cstdint>

namespace Scribble {

	class IBufferIndex
	{
	public:
		virtual ~IBufferIndex() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual const uint32_t GetCount() const = 0;

		static std::shared_ptr<IBufferIndex> Create(uint32_t* indices, uint32_t count);
	};

}
