#pragma once
#include <vector>
#include "WindowsWindow.h"

namespace GE {
	class __declspec(dllexport) WindowsManager
	{
	private:
		std::vector<Window*> _windows;
	public:
		Window* find(HWND hwnd);

		void register_window(Window* wnd);
		void remove_window(Window* wnd);

		static WindowsManager* instance();
	};
}