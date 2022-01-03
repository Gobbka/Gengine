#pragma once
#include "Bindable.h"

namespace Render
{
	class IBlendEngine : public Bindable
	{
	public:
		IBlendEngine(Core::GraphicsContext*context)
			: Bindable(context)
		{}
	};
}
