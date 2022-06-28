#pragma once
#include <Types/Types.h>

#include "IEvent.h"

namespace UI
{
	enum class MouseButton {
		none,
		left,
		middle,
		right
	};

	class __declspec(dllexport) MouseEvent : public IEvent
	{
	public:
		MouseEvent(InteractiveElement* target,Position2 delta,Position2 screen)
			: IEvent(target)
			, delta(delta)
			, screen(screen)
			, button(MouseButton::none)
		{
		}

		Position2 delta;
		Position2 screen;
		MouseButton button;
	};
}
