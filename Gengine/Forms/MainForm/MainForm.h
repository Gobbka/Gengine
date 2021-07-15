#pragma once
#include "WindowsWindow.h"

namespace UI {
	class Panel;
}

namespace Forms
{
	class MainForm : public Core::WindowsWindow
	{
	private:
		UI::Panel* topbar_panel;
		
	public:
		MainForm(HINSTANCE hinst, UINT width, UINT height);
	};
}
