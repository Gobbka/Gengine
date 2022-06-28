#pragma once

namespace UI {
	class InteractiveElement;

	class IEvent
	{
	public:
		IEvent(InteractiveElement* target)
			: target(target)
		{
		}

		InteractiveElement* target;
	};
}