#pragma once
#include "../../Common/GraphicsCommon.h"

namespace Render {
	class __declspec(dllexport) IShader
	{
	protected:
		GEGraphics* context;

		explicit IShader(GEGraphics* engine) : context(engine) {}
	};
}
