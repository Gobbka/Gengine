#include "WindowsManager.h"

GE::Window* GE::WindowsManager::get_by_hwnd(HWND hwnd)
{
	for(auto*wnd : _windows)
	{
		if (wnd->hwnd() == hwnd)
			return wnd;
	}

	return nullptr;
}

GE::Window* GE::WindowsManager::create_window(HINSTANCE hinst, UINT width, UINT height)
{
	auto* new_window = new Window(hinst,width,height);

	register_window(new_window);

	return new_window;
}

void GE::WindowsManager::register_window(Window* wnd)
{
	_windows.push_back(wnd);
}

void GE::WindowsManager::remove_window(Window* wnd)
{
	// TODO: complete
}

GE::WindowsManager* GE::WindowsManager::instance()
{
	static auto* instance = new WindowsManager();
	return instance;
}
