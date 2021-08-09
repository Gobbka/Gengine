#pragma once
#include <d3d11.h>

#include "BufferAllocator.h"
#include "Canvas/CanvasLayer.h"
#include "Graphics/Material/Material.h"
#include "Render/Engine/RenderTarget.h"
#include "Render/Engine/SpriteEngine.h"
#include "Render/Model/Model.h"


// TODO-LIST:
// Rename D3DEngine to Camera and replace all D3DEngine* dependency to Graphic*
//

namespace Render {
	class RenderTarget;
	class Texture;
	class SamplerState;
	class VertexShader;
	class PixelShader;
	class Camera;
}

namespace Core
{
	struct __declspec(dllexport) WorldSpace {
		std::vector<Render::Model*> objects;

		void add_object(Render::Model* object);
	};
	
	class __declspec(dllexport) GraphicsContext
	{
	public:
		ID3D11DeviceContext* context;
		ID3D11Device* device;
	private:
		Surface _screen_resolution;
		
		IDXGISwapChain* _swap;
		Render::RenderTarget _targetView;

		Render::SamplerState* _samplerState;
		
		Render::PixelShader* _pixelShader;
		//Render::VertexShader* _vertexShader;
		//Render::VertexShader* _vertexShader3d;
		
		ID3D11InputLayout* _inputLayout;

		D3D11_VIEWPORT _viewport;
		Render::IBufferAllocator* _bufferAllocator;
	private:
		GraphicsContext(ID3D11Device*, IDXGISwapChain*, ID3D11DeviceContext*);
		
		Render::SpriteEngine* _spriteEngine;
		
		WorldSpace _worldSpace;
	public:
		Render::IBufferAllocator* buffer_allocator() const;

		
		WorldSpace* worldspace();
		
		Render::SpriteEngine* get_sprite_engine();
		
		Surface get_screen_resolution() const;
		Render::RenderTarget* get_render_target_view();

		/// <summary>
		/// create and returns camera pointer
		/// </summary>
		/// <param name="target">pointer to render target.If nullptr passed,camera will create from swap chain</param>
		/// <returns></returns>
		Render::Camera* create_camera(Render::RenderTarget*target);
	public:
		void set_resolution(Surface new_resolution);
		
		void clear(Color3 color);

		void new_frame();
		void present_frame();

		void begin_2d();
		void begin_3d();
	public:
		Render::Texture* create_texture(Render::Material* material);
		
		static GraphicsContext* new_context(HWND hwnd,Surface size);
	};
}
