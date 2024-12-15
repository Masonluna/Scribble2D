#pragma once
#include "scbpch.h"
#include "IBufferVertex.h"
#include "IBufferIndex.h"

namespace Scribble {

	class IVertexArray
	{
	public:
		virtual ~IVertexArray() = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;


		static std::shared_ptr<IVertexArray> Create();
	};

}