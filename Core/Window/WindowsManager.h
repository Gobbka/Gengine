#pragma once
#include <vector>
#include "WindowsWindow.h"

namespace GE {
	class __declspec(dllexport) WindowsManager
	{
	private:
		std::vector<Window*> _windows;
	public:
		Window* get_by_hwnd(HWND hwnd);

		Window* create_window(HINSTANCE hinst, UINT width = 800u, UINT height = 600u);
		void register_window(Window* wnd);
		void remove_window(Window* wnd);

		static WindowsManager* instance();
	};
}