#include "scbpch.h"
#include "Layer.h"

namespace Scribble {
	Layer::Layer(const std::string& debugName)
		: m_DebugName(debugName)
	{}

	Layer::~Layer() 
	{}
}