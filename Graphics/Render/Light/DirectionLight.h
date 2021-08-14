#pragma once
#include "../Viewer/WorldViewer.h"
#include "Types/Transform.h"

namespace Core {
	class GraphicsContext;
}

namespace Render
{
	class MaskEngine;

	class __declspec(dllexport) DirectionLight : public WorldViewer
	{
		MaskEngine* _mask_engine;
	public:

		DirectionLight(Core::GraphicsContext* context);

		void create_shadowmap();
	};
}
