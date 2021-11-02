#pragma once
#include "../Bindable.h"

namespace Render {
	class IShader
	{
	protected:
		Core::GraphicsContext* context;

		explicit IShader(Core::GraphicsContext* engine) : context(engine) {}
	};
}
