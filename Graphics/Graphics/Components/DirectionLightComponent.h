#pragma once
#include "../../Render/Viewer/WorldViewer.h"
#include "../../Render/Common/GraphicsCommon.h"

namespace Render
{
	struct __declspec(dllexport) DirectionLightComponent : WorldViewer
	{
		Core::DX11Graphics* context;
		GEMaskEngine* mask_engine;

		explicit DirectionLightComponent(Core::DX11Graphics* context);
		DirectionLightComponent(DirectionLightComponent&& other) noexcept;
		DirectionLightComponent& operator=(DirectionLightComponent&& other) noexcept;

		void bind() const;
	};
}
