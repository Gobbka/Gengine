#include "WindowsManager.h"

GE::Window* GE::WindowsManager::find(HWND hwnd)
{
	for(auto*wnd : _windows)
	{
		if (wnd->hwnd() == hwnd)
			return wnd;
	}

	return nullptr;
}

void GE::WindowsManager::register_window(Window* wnd)
{
	_windows.push_back(wnd);
}

void GE::WindowsManager::remove_window(Window* wnd)
{
	// TODO: complete
	for(UINT i = 0;i < _windows.size();i++)
	{
		if (_windows[i] == wnd)
			_windows.erase(_windows.begin()+i);
	}

	if(_windows.size() == 0)
	{
		exit(0);
	}
}

GE::WindowsManager* GE::WindowsManager::instance()
{
	static auto* instance = new WindowsManager();
	return instance;
}
