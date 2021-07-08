#include "WindowsWindow.h"

#include <cassert>
#include <iostream>


#include "WindowsManager.h"

LRESULT Core::WindowsWindow::window_procedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{	
	auto* window = (WindowsWindow*)WindowsManager::instance()->get_by_hwnd(hwnd);
	
	if(!window)
		return DefWindowProc(hwnd, msg, wParam, lParam);

	if (window->on_wndproc)
		window->on_wndproc(msg, wParam, lParam);
	
	if (msg == WM_CLOSE)
		exit(0);

	if(msg == WM_SIZE)
	{
		const auto window_width  = LOWORD(lParam);
		const auto window_height = HIWORD(lParam);

		std::cout << window_width << " " << window_height << '\n';

		if(window->on_resize)
			window->on_resize(Surface((float)window_width, (float)window_height));
	}
	
	if (msg == WM_SIZING)
	{
		RECT r = *(RECT*)lParam;
		
		const auto window_width = r.right - r.left;
		const auto window_height = r.bottom - r.top;
		
		if (window_width > window->max_width)
			((RECT*)lParam)->right = r.left + window->max_width;

		if (window_height > window->max_height)
			((RECT*)lParam)->bottom = r.top + window->max_height;

		
	}
	
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void Core::WindowsWindow::handle_resize(RECT* lprect)
{
	auto rect = *lprect;
	_size = Surface(rect.right - rect.left, rect.bottom - rect.top);
	this->on_resize(_size);
}

Core::WindowsWindow::WindowsWindow(HINSTANCE hint, UINT width, UINT height)
	: _size(width,height)
{
	_hInst = hint;

	const auto* class_name = L"GENGINE";
	WNDCLASSEXW wndClass
	{
		sizeof(WNDCLASSEXW),
		CS_OWNDC,
		window_procedure,
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
		WS_CAPTION|WS_MINIMIZEBOX| WS_SIZEBOX | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width, height,
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
