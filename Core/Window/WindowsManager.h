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

		bool hasLiveWindows() const;
		void registerWindow(Window* wnd);
		void removeWindow(Window* wnd);

		auto begin() { return _windows.begin(); }
		auto end() { return _windows.end(); }

		static WindowsManager* instance();
	};
}