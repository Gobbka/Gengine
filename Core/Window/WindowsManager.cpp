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

bool GE::WindowsManager::hasLiveWindows() const
{
	return _windows.size() > 0;
}

void GE::WindowsManager::registerWindow(Window* wnd)
{
	_windows.push_back(wnd);
}

void GE::WindowsManager::removeWindow(Window* wnd)
{
	for(UINT i = 0;i < _windows.size();i++)
	{
		if (_windows[i] == wnd)
		{
			_windows.erase(_windows.begin()+i);
		}
	}
}

GE::WindowsManager* GE::WindowsManager::instance()
{
	static auto* instance = new WindowsManager();
	return instance;
}
