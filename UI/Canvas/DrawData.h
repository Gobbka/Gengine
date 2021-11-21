#pragma once
#include "DrawCmd.h"
#include "DynamicAllocator.h"
#include "Vertex2D.h"

namespace Canvas
{
	struct DrawData
	{
		DynamicAllocator<DrawCmd> draw_list;
		DynamicAllocator<UI::Vertex2D> vertices;
		DynamicAllocator<UINT> indices;

		Render::Texture* default_texture;

		DrawData()
			: draw_list(100)
			, vertices(100)
			, indices(100)
			, default_texture(nullptr)
		{}
	};
}
