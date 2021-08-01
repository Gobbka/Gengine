#pragma once
#include "../../Render/d3d/Bindable.h"

namespace Render
{
	class IIndexBuffer : public Bindable
	{
	public:
		IIndexBuffer(Core::GraphicsContext* context) : Bindable(context) {}
	};
}
