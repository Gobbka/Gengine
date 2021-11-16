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
	};
}
