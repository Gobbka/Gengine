#pragma once
#include "../Viewer/WorldViewer.h"
#include "Types/Transform.h"

namespace Core {
	class GraphicsContext;
}

namespace Render
{
	class MaskEngine;

	class __declspec(dllexport) DirectionLightComponent : public WorldViewer
	{
	public:

		DirectionLightComponent(Core::GraphicsContext* context);

		void bind();
	};
}
