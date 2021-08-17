#pragma once
#include <vector>

#include "../../Render/d3d/Bindable.h"

namespace Render
{
	typedef void(*BindFunction)();
	
	class Step
	{
		std::vector<BindFunction> _binds;
	public:
		void add_bindable(BindFunction bind);

		void bind();
	};
}
