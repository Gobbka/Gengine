#pragma once
#include <Windows.h>
#include "window.h"

namespace Core {
	class __declspec(dllexport) WindowsWindow : IWindow
	{
	private:
		static LRESULT CALLBACK window_procedure(HWND, UINT, WPARAM, LPARAM);
	private:
		
		HINSTANCE _hInst;
		HWND _hwnd;
		
	public:
		WindowsWindow(HINSTANCE hinst);

		void show();
		void hide();

		HWND hwnd();
	};
}
