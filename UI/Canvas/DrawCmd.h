#pragma once
#include <Render/Common/Texture.h>

namespace Canvas {
	struct DrawCmd
	{
		Render::GETexture* texture;
		unsigned idx_offset;
		unsigned idx_count;
		unsigned vtx_count;
		unsigned vtx_offset;
	};
}
