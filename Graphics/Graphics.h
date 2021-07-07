#pragma once
#include <d3d11.h>
#include <vector>
#include "Canvas/CanvasLayer.h"
#include "Graphics/Types.h"
#include "Render/Layer/ILayer.h"


namespace Render {
	class D3DEngine;
}

namespace Core
{
	class __declspec(dllexport) GraphicsContext
	{
	private:
		Surface _screen_resolution;
		
		ID3D11Device* _device;
		IDXGISwapChain* _swap;
		ID3D11DeviceContext* _context;
		ID3D11RenderTargetView* _targetView;

		ID3D11VertexShader* _vertexShader;
		ID3D11PixelShader* _pixelShader;
		ID3D11InputLayout* _inputLayout;

		D3D11_VIEWPORT _viewport;
	private:
		GraphicsContext(ID3D11Device*, IDXGISwapChain*, ID3D11DeviceContext*);

		std::vector<Canvas::Canvas2DLayer*> _2d_layers;
		Render::D3DEngine* _engine;
	public:
		ID3D11Device* device() const;
		ID3D11DeviceContext* context() const;
		Surface get_screen_resolution() const;
		ID3D11RenderTargetView* get_render_target_view();
		
		Canvas::Canvas2DLayer* create_2d_layer();
	public:
		void set_resolution(Surface new_resolution);
		
		void clear();
		
		void present() const;
	public:
		static GraphicsContext* new_context(HWND hwnd);
	};
}
