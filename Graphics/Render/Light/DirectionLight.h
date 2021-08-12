#pragma once
#include "Types/Transform.h"

namespace Core {
	class GraphicsContext;
}

namespace Render
{
	class DirectionLight
	{
		Core::GraphicsContext* _context;
	public:
		Core::Transform transform;

		DirectionLight(Core::GraphicsContext* context);
	};
}
