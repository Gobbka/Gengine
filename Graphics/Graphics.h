#pragma once
#include <d3d11.h>
#include <vector>


#include "Render/Layer/ILayer.h"

namespace Render {
	class D3DEngine;
}

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

		std::vector<Render::I2DLayer*> _2d_layers;
		Render::D3DEngine* _engine;
	public:
		ID3D11Device* device() const;
		ID3D11DeviceContext* context() const;
	public:
		void clear();
		
		void present() const;
	public:
		static GraphicsContext* new_context(HWND hwnd);
	};
}
