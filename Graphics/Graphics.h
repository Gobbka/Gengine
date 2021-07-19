#pragma once
#include <d3d11.h>
#include <vector>
#include "Canvas/CanvasLayer.h"
#include "Graphics/Types.h"
#include "Graphics/Material/Material.h"
#include "Render/Engine/SpriteEngine.h"
#include "Render/Layer/ILayer.h"


// TODO-LIST:
// Rename D3DEngine to Camera and replace all D3DEngine* dependency to Graphic*
//

namespace Render {
	class Texture;
	class SamplerState;
	class VertexShader;
	class PixelShader;
	class Camera;
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
		
		Render::PixelShader* _pixelShader;
		Render::VertexShader* _vertexShader;
		Render::VertexShader* _vertexShader3d;
		
		ID3D11InputLayout* _inputLayout;

		D3D11_VIEWPORT _viewport;

	private:
		GraphicsContext(ID3D11Device*, IDXGISwapChain*, ID3D11DeviceContext*);
		
		Render::Camera* _main_camera;
		Render::SpriteEngine* _spriteEngine;

	public:
		Render::SpriteEngine* get_sprite_engine();
		
		ID3D11Device* device() const;
		ID3D11DeviceContext* context() const;
		Surface get_screen_resolution() const;
		ID3D11RenderTargetView* get_render_target_view();

		Render::Camera* main_camera();

		bool create_buffer(D3D11_BUFFER_DESC* desc, D3D11_SUBRESOURCE_DATA* data, ID3D11Buffer** buffer) const;
	public:
		void set_resolution(Surface new_resolution);
		
		void clear(Color3 color);
		
		void present() const;

		void begin_2d();
		void begin_3d();
	public:
		Render::Texture* create_texture(Render::Material* material);
		void set_texture(Render::Texture* texture);
		
		static GraphicsContext* new_context(HWND hwnd);
	};
}
