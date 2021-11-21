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

	if (msg == WM_KEYDOWN)
	{
		window->keyboard->set((VirtualKey)wParam, true);
	}
	if (msg == WM_KEYUP)
	{
		window->keyboard->set((VirtualKey)wParam, false);
	}

	if (msg == WM_CLOSE)
		exit(0);

	if(msg == WM_SIZE)
	{
		const auto window_width  = LOWORD(lParam);
		const auto window_height = HIWORD(lParam);

		std::cout << window_width << " " << window_height << '\n';
		window->handle_resize(Surface(window_width,window_height));
	}
	
	if (msg == WM_SIZING)
	{
		RECT r = *(RECT*)lParam;
		
		const auto window_width  = (UINT)( r.right - r.left );
		const auto window_height = (UINT)( r.bottom - r.top );
		
		if (window_width > window->max_width)
			((RECT*)lParam)->right = r.left + window->max_width;

		if (window_height > window->max_height)
			((RECT*)lParam)->bottom = r.top + window->max_height;
	}
	
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void Core::WindowsWindow::handle_resize(Surface rect)
{
	_size = rect;

	if(this->on_resize)
		this->on_resize(rect);
}

Core::WindowsWindow::WindowsWindow(HINSTANCE hint, UINT width, UINT height,HICON icon)
	: _size(width,height)
	, keyboard(new Keyboard())
{
	_hInst = hint;
	
	const auto* class_name = L"GENGINE";
	WNDCLASSEXW wndClass
	{
		sizeof(WNDCLASSEXW),
		CS_OWNDC | CS_DBLCLKS,
		window_procedure,
		0,0,
		_hInst,nullptr,LoadCursor(nullptr,IDC_ARROW),nullptr,
		nullptr,
		class_name,
		icon
	};
	auto result = RegisterClassExW(&wndClass);
	assert(result != 0);

	int centerScreenX = GetSystemMetrics(SM_CXSCREEN) / 2 - width / 2;
	int centerScreenY = GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2;

	RECT wr; //Widow Rectangle
	wr.left = centerScreenX;
	wr.top = centerScreenY;
	wr.right = wr.left + width;
	wr.bottom = wr.top + height;
	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

	_hwnd = CreateWindowExW(
		0,
		class_name,
		L"GENIGNE MAIN",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU,
		wr.left, //Window X Position
		wr.top, //Window Y Position
		wr.right - wr.left, //Window Width
		wr.bottom - wr.top, //Window Height
		0,
		0,
		_hInst,
		0
	);

	assert(_hwnd != nullptr);

	_size = Surface(width, height);
	WindowsManager::instance()->register_window(this);
}

void Core::WindowsWindow::show()
{
	ShowWindow(_hwnd, SW_SHOW);
}

void Core::WindowsWindow::hide()
{
	ShowWindow(_hwnd, SW_HIDE);
}

void Core::WindowsWindow::peek()
{
	MSG msg;

	if (PeekMessage(&msg, _hwnd, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

HWND Core::WindowsWindow::hwnd()
{
	return _hwnd;
}

Surface Core::WindowsWindow::size()
{
	return _size;
}
