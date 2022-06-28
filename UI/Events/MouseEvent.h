#pragma once
#include <Types/Types.h>

#include "IEvent.h"

namespace UI
{
	class __declspec(dllexport) MouseEvent : public IEvent
	{
	public:
		MouseEvent(InteractiveElement* target,Position2 delta,Position2 screen)
			: IEvent(target)
			, delta(delta)
			, screen(screen)
		{
		}

		Position2 delta;
		Position2 screen;
	};
}
