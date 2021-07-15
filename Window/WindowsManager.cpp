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

Core::WindowsWindow* Core::WindowsManager::create_window(HINSTANCE hinst, UINT width, UINT height)
{
	auto* new_window = new Core::WindowsWindow(hinst,width,height);

	register_window(new_window);

	return new_window;
}

void Core::WindowsManager::register_window(WindowsWindow* wnd)
{
	_windows.push_back(wnd);
}

Core::WindowsManager* Core::WindowsManager::instance()
{
	static auto* instance = new WindowsManager();
	return instance;
}
