#pragma once
#include "../../Render/Viewer/WorldViewer.h"
#include "../../Render/Common/GraphicsCommon.h"

namespace Render
{
	struct __declspec(dllexport) DirectionLightComponent : WorldViewer
	{
		GEGraphics* context;
		GEMaskEngine* mask_engine;

		explicit DirectionLightComponent(GEGraphics* context);
		DirectionLightComponent(DirectionLightComponent&& other) noexcept;
		DirectionLightComponent& operator=(DirectionLightComponent&& other) noexcept;

		void bind() const;
	};
}
