#include "WindowsManager.h"

Core::WindowsWindow* Core::WindowsManager::get_by_hwnd(HWND hwnd)
{
	for(auto*wnd : _windows)
	{
		if (wnd->hwnd() == hwnd)
			return wnd;
	}

	return nullptr;
}

Core::WindowsWindow* Core::WindowsManager::create_window(HINSTANCE hints)
{
	auto* new_window = new Core::WindowsWindow(hints);
	
	_windows.push_back(new_window);

	return new_window;
}

Core::WindowsManager* Core::WindowsManager::instance()
{
	static auto* instance = new WindowsManager();
	return instance;
}
