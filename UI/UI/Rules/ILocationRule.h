#pragma once
#include "Types/Types.h"

namespace UI
{
	class ChildrenCollection;

	class __declspec(dllexport) ILocationRule
	{
	public:
		virtual void place_on(Position2 base_position, Surface resolution) =0;
		virtual ~ILocationRule() = default;
	};
}
