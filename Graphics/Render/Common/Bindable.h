#pragma once
#include "GraphicsCommon.h"

namespace Render
{
	class __declspec(dllexport) Bindable
	{
	protected:
		GEGraphics* _engine;
	public:
		Bindable(GEGraphics*engine)
			: _engine(engine)
		{}

		virtual ~Bindable() = default;

		virtual void bind() = 0;
	};
}
