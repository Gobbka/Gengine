#include "DrawData.h"

Canvas::DrawData::DrawData()
	: draw_list(100)
	, allocator(100)
	, default_texture(nullptr)
{}
