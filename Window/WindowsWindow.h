﻿#pragma once
#include "Types/Types.h"

#include <functional>
#include <Windows.h>


namespace Core {
	class __declspec(dllexport) WindowsWindow
	{
	private:
		static LRESULT CALLBACK window_procedure(HWND, UINT, WPARAM, LPARAM);
	private:
		
		HINSTANCE _hInst;
		HWND _hwnd;
		Surface _size;
	protected:
		virtual void handle_resize(Surface rect);
		
	public:
		UINT max_width = 0xFFFFFF;
		UINT max_height = 0xFFFFFF;
		UINT min_width = 50;
		UINT min_height = 50;
	public:
		std::function<void(Surface)> on_resize;
		std::function<void(UINT msg,WPARAM wParam,LPARAM lParam)> on_wndproc;
		
		WindowsWindow(HINSTANCE hinst,UINT width=800u,UINT height=600u);

		void show();
		void hide();

		HWND hwnd();
		Surface size();
	};
}
