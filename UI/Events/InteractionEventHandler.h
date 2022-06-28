#pragma once
#include "MouseEvent.h"

enum class EventStatus
{
	none = false,
	handled = true,
};

namespace UI
{
	class IEventHandler
	{
	public:
		virtual ~IEventHandler() = default;
	protected:
		bool can_handle_event = true;

		virtual void onMouseDown(MouseButton button) PURE;
		virtual void onMouseUp(MouseButton button) PURE;
		virtual void onMouseScroll(short direction) PURE;
		virtual void onMouseMove(int mx, int my) PURE;
		virtual void onDbClick() PURE;
	};
}
