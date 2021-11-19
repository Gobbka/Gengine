#pragma once
#include "../Bindable.h"

namespace Render {
	class __declspec(dllexport) IShader
	{
	protected:
		Core::GraphicsContext* context;

		explicit IShader(Core::GraphicsContext* engine) : context(engine) {}
	};
}
