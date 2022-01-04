#include "DepthStencilStatesCollection.h"
#include "../Render/Common/DepthStencil.h"

Render::DepthFunc get_depth_func(Render::DSBitSet bitset)
{
	if (bitset & (Render::DSBitSet)Render::DepthStencilUsage::depth)
		return Render::DepthFunc::depth_less;
	if (bitset & (Render::DSBitSet)Render::DepthStencilUsage::depth_equal)
		return Render::DepthFunc::depth_equal;
	return Render::DepthFunc::none;
}

Render::DepthStencilStatesCollection::DepthStencilStatesCollection(Core::DX11Graphics* context)
	: _context(context)
{
}

Render::GEDepthStencil Render::DepthStencilStatesCollection::operator[](DSBitSet index)
{
	auto element = _map[index];
	if(!element.valid())
	{
		DepthStencilDesc ds_desc;
		ds_desc.depth = get_depth_func(index);
		ds_desc.stencil_usage = (StencilUsage)(index >> 2);

		element = GEDepthStencil(_context, ds_desc);
		_map[index] = element;
	}
	return element;
}
