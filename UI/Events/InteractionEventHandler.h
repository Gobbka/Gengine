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
		virtual void on_mouse_scroll(short direction) PURE;
		virtual void on_mouse_move(int mx, int my) PURE;
		virtual void on_db_click() PURE;
	};
}
