#include "scbpch.h"
#include "Scribble2D/Core/Layer.h"

namespace Scribble {
	Layer::Layer(const std::string& debugName)
		: m_DebugName(debugName)
	{}

	Layer::~Layer() 
	{}
}