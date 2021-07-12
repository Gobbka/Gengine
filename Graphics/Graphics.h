#pragma once
#include <d3d11.h>
#include <vector>
#include "Canvas/CanvasLayer.h"
#include "Graphics/Types.h"
#include "Graphics/Material/Material.h"
#include "Render/Layer/ILayer.h"


// TODO-LIST:
// Rename D3DEngine to Camera and replace all D3DEngine* dependency to Graphic*
//

namespace Render {
	class Texture;
	class SamplerState;
	class VertexShader;
	class PixelShader;
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

		Render::SamplerState* _samplerState;
		ID3D11InputLayout* _texture_layout;
		
		Render::PixelShader* _pixelShader;
		Render::VertexShader* _vertexShader;

		Render::PixelShader* _texture_ps;
		Render::VertexShader* _texture_vs;
		
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

		Render::D3DEngine* get_2d_engine();
		
		Canvas::Canvas2DLayer* create_2d_layer();
		void append_2d_layer(Canvas::Canvas2DLayer*layer);
	public:
		void set_resolution(Surface new_resolution);
		
		void clear(Color3 color);
		
		void present() const;
	public:
		Render::Material* create_material(Surface resolution,char* pointer);
		Render::Texture* create_texture(Render::Material* material);
		void set_texture(Render::Texture* texture);
		
		static GraphicsContext* new_context(HWND hwnd);
	};
}
