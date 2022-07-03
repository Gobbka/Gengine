#include "WinIntEventHandler.h"

#include <iostream>
#include <windowsx.h>

void UI::Interaction::WinIntEventHandler::windowProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (!this->can_handle_event)
		return;
	
	if(msg == WM_MOUSEWHEEL)
	{
		this->onMouseScroll(GET_WHEEL_DELTA_WPARAM(wParam));
	}

	if(msg == WM_MOUSEMOVE)
	{
		this->onMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	}

	if (msg == WM_LBUTTONUP)
	{
		this->onMouseUp(MouseButton::left);
	}

	if (msg == WM_LBUTTONDOWN)
	{
		this->onMouseDown(MouseButton::left);
	}

	if(msg == WM_RBUTTONUP)
	{
		onMouseUp(MouseButton::right);
	}

	if (msg == WM_RBUTTONDOWN)
	{
		onMouseDown(MouseButton::right);
	}

	if(msg == WM_LBUTTONDBLCLK)
	{
		this->onDbClick();
		//this->on_lbmouse_down();
		//Sleep(5);
		//this->on_lbmouse_up();
	}
}
