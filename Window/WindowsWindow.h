#pragma once
#include <Windows.h>

namespace Core {
	class __declspec(dllexport) WindowsWindow
	{
	private:
		static LRESULT CALLBACK window_procedure(HWND, UINT, WPARAM, LPARAM);
	private:
		
		HINSTANCE _hInst;
		HWND _hwnd;

	public:
		UINT max_width = 0xFFFFFF;
		UINT max_height = 0xFFFFFF;
		UINT min_width = 50;
		UINT min_height = 50;
	public:
		WindowsWindow(HINSTANCE hinst);

		void show();
		void hide();

		HWND hwnd();
	};
}