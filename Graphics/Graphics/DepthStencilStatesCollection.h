#pragma once
#include "../Render/Common/DepthStencil.h"
#include <map>

namespace Render {
	typedef __int8 DSBitSet;

	enum class DepthStencilUsage : DSBitSet
	{
		depth = 0b1,
		depth_equal = 0b10,
		stencil_normal = (DSBitSet)StencilUsage::normal << 2,
		stencil_write = (DSBitSet)StencilUsage::write << 2,
		stencil_mask = (DSBitSet)StencilUsage::mask << 2,
	};

	class __declspec(dllexport) DepthStencilStatesCollection
	{
		GEGraphics* _context;
		std::map<DSBitSet, GEDepthStencil> _map;
	public:
		DepthStencilStatesCollection(GEGraphics*context);

		GEDepthStencil operator[](DSBitSet index);
	};
}
