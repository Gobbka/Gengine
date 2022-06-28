#include "WinIntEventHandler.h"

#include <iostream>
#include <windowsx.h>

void UI::Interaction::WinIntEventHandler::windowProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (!this->can_handle_event)
		return;
	
	if(msg == WM_MOUSEWHEEL)
	{
		this->on_mouse_scroll(GET_WHEEL_DELTA_WPARAM(wParam));
	}

	if(msg == WM_MOUSEMOVE)
	{
		this->on_mouse_move(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	}

	if (msg == WM_LBUTTONUP)
	{
		this->on_lbmouse_up();
	}

	if (msg == WM_LBUTTONDOWN)
	{
		this->on_lbmouse_down();
	}

	if(msg == WM_LBUTTONDBLCLK)
	{
		this->on_db_click();
		//this->on_lbmouse_down();
		//Sleep(5);
		//this->on_lbmouse_up();
	}
}
