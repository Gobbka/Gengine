#include "DepthStencilStatesCollection.h"
#include "../Render/Engine/DepthStencil.h"

Render::DepthStencilStatesCollection::DepthStencilStatesCollection(Core::GraphicsContext* context)
{
	_context = context;
}

Render::DepthStencil* Render::DepthStencilStatesCollection::operator[](DSBitSet index)
{
	auto* element = &_map[index];
	if(element == nullptr)
	{
		DepthStencilDesc ds_desc;
		ds_desc.depth = index & (DSBitSet)DepthStencilUsage::depth;
		ds_desc.stencil_usage = (StencilUsage)(index >> 1);
		_map[index] = std::move(DepthStencil(_context, ds_desc));
	}
	return element;
}
