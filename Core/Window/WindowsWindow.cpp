﻿#include "WindowsWindow.h"

#include <cassert>
#include <iostream>
#include "WindowsManager.h"

LRESULT GE::Window::window_procedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{	
	auto* window = WindowsManager::instance()->find(hwnd);

	if (window) {

		if (msg == WM_KEYDOWN)
		{
			window->keyboard->set((VirtualKey)wParam, true);
		}
		if (msg == WM_KEYUP)
		{
			window->keyboard->set((VirtualKey)wParam, false);
		}

		if (msg == WM_CLOSE)
			delete window;

		if (msg == WM_SIZE)
		{
			const auto window_width = LOWORD(lParam);
			const auto window_height = HIWORD(lParam);

			std::cout << window_width << " " << window_height << '\n';
			window->handle_resize(Surface(window_width, window_height));
		}

		if (msg == WM_SIZING)
		{
			const auto r = *(RECT*)lParam;

			const auto window_width = (UINT)(r.right - r.left);
			const auto window_height = (UINT)(r.bottom - r.top);

			if (window_width > window->max_width)
				((RECT*)lParam)->right = r.left + window->max_width;

			if (window_height > window->max_height)
				((RECT*)lParam)->bottom = r.top + window->max_height;
		}

		if (window->on_wndproc)
			window->on_wndproc(msg, wParam, lParam);
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void GE::Window::handle_resize(Surface rect)
{
	_size = rect;

	if(this->on_resize)
		this->on_resize(rect);
}

GE::Window::Window(const wchar_t*name,HINSTANCE hint, UINT width, UINT height,HICON icon)
	: _hInst(hint)
	, _size(width,height)
	, keyboard(new Keyboard())
{
	const auto* class_name = TEXT("GEWindow");
	static bool class_registered = false;
	if(!class_registered)
	{
		const WNDCLASSEX wndClass
		{
			sizeof(WNDCLASSEX),
			CS_OWNDC | CS_DBLCLKS,
			window_procedure,
			0,0,
			_hInst,nullptr,LoadCursor(nullptr,IDC_ARROW),nullptr,
			nullptr,
			class_name,
			icon
		};
		const auto result = RegisterClassEx(&wndClass);
		assert(result != 0);

		class_registered = true;
	}


	const int centerScreenX = GetSystemMetrics(SM_CXSCREEN) / 2 - width / 2;
	const int centerScreenY = GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2;

	RECT wr; //Widow Rectangle
	wr.left = centerScreenX;
	wr.top = centerScreenY;
	wr.right = wr.left + width;
	wr.bottom = wr.top + height;
	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

	_hwnd = CreateWindowExW(
		0,
		class_name,
		name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU,
		wr.left, //Window X Position
		wr.top, //Window Y Position
		wr.right - wr.left, //Window Width
		wr.bottom - wr.top, //Window Height
		nullptr,
		nullptr,
		_hInst,
		nullptr
	);

	assert(_hwnd != nullptr);

	WindowsManager::instance()->register_window(this);
}

void GE::Window::show()
{
	ShowWindow(_hwnd, SW_SHOW);
}

void GE::Window::hide()
{
	ShowWindow(_hwnd, SW_HIDE);
}

void GE::Window::peek()
{
	MSG msg;

	while(PeekMessage(&msg, _hwnd, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

HWND GE::Window::hwnd()
{
	return _hwnd;
}

Surface GE::Window::size()
{
	return _size;
}
