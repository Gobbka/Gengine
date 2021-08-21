#pragma once
#include "Types/Types.h"

namespace Render
{
	struct ColorComponent
	{
		Color3 color;

		ColorComponent(Color3 color = Color3::black()) : color(color){}
	};
}
