#include "WindowsWindow.h"

#include <cassert>

LRESULT Core::WindowsWindow::window_procedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

Core::WindowsWindow::WindowsWindow(HINSTANCE hint)
{
	_hInst = hint;
	
	auto* class_name = L"GENGINE";
	WNDCLASSEXW wndClass
	{
		sizeof(WNDCLASSEXW),
		CS_OWNDC | CS_DROPSHADOW,
		DefWindowProc,
		0,0,
		_hInst,nullptr,nullptr,nullptr,
		nullptr,
		class_name,
		nullptr
	};

	assert(RegisterClassExW(&wndClass) != 0);

	_hwnd = CreateWindowExW(
		0,
		class_name,
		L"GENIGNE MAIN",
		WS_CAPTION|WS_MINIMIZEBOX,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		500, 500,
		0,
		0,
		_hInst,
		0
	);

	if(_hwnd == 0)
	{
		auto error = GetLastError();
		error = 228;
	}
}

void Core::WindowsWindow::show()
{
	ShowWindow(_hwnd, SW_SHOW);
}

void Core::WindowsWindow::hide()
{
	ShowWindow(_hwnd, SW_HIDE);
}

HWND Core::WindowsWindow::hwnd()
{
	return _hwnd;
}
