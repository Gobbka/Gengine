#pragma once
#include <vector>

#include "DrawCmd.h"

namespace Canvas
{
	struct DrawData
	{
		std::vector<DrawCmd> draw_list{100};
	};
}
