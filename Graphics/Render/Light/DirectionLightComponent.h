#pragma once
#include "../Viewer/WorldViewer.h"
#include "../Common/GraphicsCommon.h"

namespace Core {
	class GraphicsContext;
}

namespace Render
{
	struct __declspec(dllexport) DirectionLightComponent : public WorldViewer
	{
		Core::GraphicsContext* context;
		GEMaskEngine* mask_engine;

		explicit DirectionLightComponent(Core::GraphicsContext* context);
		DirectionLightComponent(DirectionLightComponent&& other) noexcept;
		DirectionLightComponent& operator=(DirectionLightComponent&& other) noexcept;

		void bind() const;
	};
}
