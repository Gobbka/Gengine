#pragma once
#include "../Types/Types.h"

#include <functional>
#include <Windows.h>

#include "../Input/Keyboard.h"

class Keyboard;

namespace GE {
	class __declspec(dllexport) Window
	{
		static LRESULT CALLBACK window_procedure(HWND, UINT, WPARAM, LPARAM);
		
		HINSTANCE _hInst;
		HWND _hwnd;
		Surface _size;
		bool _closed;
	protected:
		virtual void handleResize(Surface rect);
		
	public:
		UINT max_width = 0xFFFFFF;
		UINT max_height = 0xFFFFFF;
		UINT min_width = 50;
		UINT min_height = 50;
	public:
		Keyboard* keyboard;
		std::function<void(Surface)> on_resize;
		std::function<void(UINT msg,WPARAM wParam,LPARAM lParam)> on_wndproc;
		
		Window(const wchar_t*name,HINSTANCE hinst,UINT width=800u,UINT height=600u,HICON icon = nullptr);

		void close();
		void show() const;
		void hide() const;

		bool peek() const;

		HWND windowId() const;
		Surface size() const;
	};
}
