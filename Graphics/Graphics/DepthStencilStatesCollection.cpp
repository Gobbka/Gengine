#include "DepthStencilStatesCollection.h"
#include "../Render/Engine/DepthStencil.h"

Render::DepthFunc get_depth_func(Render::DSBitSet bitset)
{
	if (bitset & (Render::DSBitSet)Render::DepthStencilUsage::depth)
		return Render::DepthFunc::depth_less;
	if (bitset & (Render::DSBitSet)Render::DepthStencilUsage::depth_equal)
		return Render::DepthFunc::depth_equal;
	return Render::DepthFunc::none;
}

Render::DepthStencilStatesCollection::DepthStencilStatesCollection(Core::GraphicsContext* context)
	: _context(context)
{
}

Render::DepthStencil Render::DepthStencilStatesCollection::operator[](DSBitSet index)
{
	auto element = _map[index];
	if(!element.valid())
	{
		DepthStencilDesc ds_desc;
		ds_desc.depth = get_depth_func(index);
		ds_desc.stencil_usage = (StencilUsage)(index >> 2);

		element = DepthStencil(_context, ds_desc);
		_map[index] = element;
	}
	return element;
}
