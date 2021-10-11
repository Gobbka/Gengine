#pragma once
#include "../Render/Engine/DepthStencil.h"
#include <map>

namespace Core
{
	class GraphicsContext;
}

namespace Render {
	struct DepthStencil;
	typedef __int8 DSBitSet;

	enum class DepthStencilUsage : DSBitSet
	{
		depth = 0b1,
		stencil_normal = (DSBitSet)StencilUsage::normal << 1,
		stencil_write = (DSBitSet)StencilUsage::write << 1,
		stencil_mask = (DSBitSet)StencilUsage::mask << 1,
	};

	class DepthStencilStatesCollection
	{
		Core::GraphicsContext* _context;
		std::map<DSBitSet, DepthStencil> _map;
	public:
		DepthStencilStatesCollection(Core::GraphicsContext*context);

		DepthStencil* operator[](DSBitSet index);
	};
}
