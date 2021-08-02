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
		Render::VertexShader* _vertexShader;
		Render::VertexShader* _vertexShader3d;
		
		ID3D11InputLayout* _inputLayout;

		D3D11_VIEWPORT _viewport;
		Render::IBufferAllocator* _bufferAllocator;
	private:
		GraphicsContext(ID3D11Device*, IDXGISwapChain*, ID3D11DeviceContext*);
		
		Render::Camera* _main_camera;
		Render::Camera* _texture_camera;
		Render::SpriteEngine* _spriteEngine;

		Render::Texture* _texture;
		
		WorldSpace _worldSpace;
	public:
		Render::IBufferAllocator* buffer_allocator() const;
		WorldSpace* worldspace();
		
		Render::SpriteEngine* get_sprite_engine();
		
		Surface get_screen_resolution() const;
		Render::RenderTarget* get_render_target_view();

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
		
		static GraphicsContext* new_context(HWND hwnd,Surface size);
	};
}
