#include "DepthStencilStatesCollection.h"
#include "../Render/Engine/DepthStencil.h"

Render::DepthStencilStatesCollection::DepthStencilStatesCollection(Core::GraphicsContext* context)
{
	_context = context;
}

Render::DepthStencil Render::DepthStencilStatesCollection::operator[](DSBitSet index)
{
	auto element = _map[index];
	if(!element.valid())
	{
		DepthStencilDesc ds_desc;
		ds_desc.depth = index & (DSBitSet)DepthStencilUsage::depth;
		ds_desc.stencil_usage = (StencilUsage)(index >> 1);

		element = DepthStencil(_context, ds_desc);
		_map[index] = element;
	}
	return element;
}
