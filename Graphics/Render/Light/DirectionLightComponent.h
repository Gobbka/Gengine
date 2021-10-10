#pragma once
#include "../Viewer/WorldViewer.h"

namespace Core {
	class GraphicsContext;
}

namespace Render
{
	class MaskEngine;

	struct __declspec(dllexport) DirectionLightComponent : public WorldViewer
	{
		Core::GraphicsContext* context;
		MaskEngine* mask_engine;

		explicit DirectionLightComponent(Core::GraphicsContext* context);
		DirectionLightComponent(DirectionLightComponent&& other) noexcept;
		DirectionLightComponent& operator=(DirectionLightComponent&& other) noexcept;

		void bind() const;
	};
}
