#pragma once
#include "../Viewer/WorldViewer.h"

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
		void set_position(Position3 pos);
		void set_rotation(Vector3 rot);
		void bind();
	};
}
