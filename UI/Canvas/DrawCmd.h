#pragma once
#include <Render/Common/Texture.h>
#include <Render/Common/DepthStencil.h>

namespace Render
{
	enum class StencilUsage : char;
}

namespace Canvas {
	struct DrawCmd
	{
		Render::GETexture* texture;
		unsigned idx_offset;
		unsigned idx_count;
		unsigned vtx_count;
		unsigned vtx_offset;
		unsigned char stencil_layer = 0;
		Render::StencilUsage stencil_usage = Render::StencilUsage::ignore;
	};
}
