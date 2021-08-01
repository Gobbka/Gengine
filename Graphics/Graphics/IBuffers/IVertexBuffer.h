#pragma once
#include "../../Render/d3d/Bindable.h"

namespace Render
{
	class __declspec(dllexport) IVertexBuffer : public Bindable
	{
	public:
		IVertexBuffer(Core::GraphicsContext* engine) : Bindable(engine) {}

		virtual void update(unsigned update_size = -1) = 0;
	};
}
