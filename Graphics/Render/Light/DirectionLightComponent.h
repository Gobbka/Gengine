#pragma once
#include <algorithm>

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
		explicit DirectionLightComponent(Core::GraphicsContext* context);
		DirectionLightComponent(DirectionLightComponent&& other) noexcept;
		DirectionLightComponent& operator=(DirectionLightComponent&& other) noexcept;

		void set_position(Position3 pos);
		void set_rotation(Vector3 rot);
		void bind();
	};
}
