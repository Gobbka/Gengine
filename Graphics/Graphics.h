#pragma once
#include <d3d11.h>

namespace Core
{
	class __declspec(dllexport) GraphicsContext
	{
	private:
		ID3D11Device* _device;
		IDXGISwapChain* _swap;
		ID3D11DeviceContext* _context;
		ID3D11RenderTargetView* _targetView;
	private:
		GraphicsContext(ID3D11Device*, IDXGISwapChain*, ID3D11DeviceContext*);
	public:
		void clear();
		
		void present();
	public:
		static GraphicsContext* new_context(HWND hwnd);
	};
}
