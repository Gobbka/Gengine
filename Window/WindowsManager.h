#pragma once
#include <vector>
#include "WindowsWindow.h"

namespace Core {
	class __declspec(dllexport) WindowsManager
	{
	private:
		std::vector<Core::WindowsWindow*> _windows;
	public:
		Core::WindowsWindow* get_by_hwnd(HWND hwnd);

		Core::WindowsWindow* create_window(HINSTANCE hinst, UINT width = 800u, UINT height = 600u);
		void register_window(WindowsWindow* wnd);

		static WindowsManager* instance();
	};
}