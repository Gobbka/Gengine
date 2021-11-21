#pragma once

namespace Render
{
	class Texture;
}

namespace Canvas {
	struct DrawCmd
	{
		Render::Texture* texture;
		unsigned idx_offset;
		unsigned idx_count;
		unsigned vtx_count;
		unsigned vtx_offset;
	};
}
