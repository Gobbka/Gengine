#pragma once
#include <vector>

#include "DrawCmd.h"
#include "DynamicAllocator.h"
#include "Vertex2D.h"

namespace Canvas
{
	struct DrawData
	{
		DynamicAllocator<DrawCmd> draw_list;
		DynamicAllocator<UI::Vertex2D> allocator;

		DrawData();
	};
}
