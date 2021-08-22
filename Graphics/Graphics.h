#pragma once
#include <d3d11.h>

#include "BufferAllocator.h"
#include "IGDevice.h"
#include "Canvas/CanvasLayer.h"
#include "Ecs/Ecs.h"
#include "Graphics/Material/Material.h"
#include "Render/Engine/RenderTarget.h"
#include "Render/Engine/SpriteEngine.h"
#include "Render/Model/Model.h"

#include "Graphics/Layouts/PixelShaderLayout.h"
#include "Graphics/Que/IPass/Passer.h"


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
		Render::RenderTarget _shadowRenderTarget;

		Render::SamplerState* _samplerState;
		
		Render::PixelShader* _pixelShader;
		
		ID3D11InputLayout* _inputLayout;

		D3D11_VIEWPORT _viewport;
		Render::IGDevice* _gdevice;
		Render::IBufferAllocator* _bufferAllocator;
	private:
		GraphicsContext(ID3D11Device*, IDXGISwapChain*, ID3D11DeviceContext*);
		
		Render::SpriteEngine* _spriteEngine;
		
		ECS::World* _worldSpace;
		ECS::Entity* _main_camera;
		Render::Passer _passer;
		
	public:
		Render::IBufferAllocator* buffer_allocator() const;

		Render::PixelShaderLayout pixel_shader;
		
		ECS::World* worldspace();
		
		Render::SpriteEngine* get_sprite_engine();
		
		Surface get_screen_resolution() const;
		Render::RenderTarget* get_render_target_view();
		Render::RenderTarget* get_shadow_render_target();


		Render::IGDevice* get_device();

		void bind_main_camera(ECS::Entity* ent);
		ECS::Entity* get_main_camera();
	public:
		void set_resolution(Surface new_resolution);

		void make_frame();
		void present_frame();
	public:
		Render::Texture* create_texture(Render::Material* material);
		
		static GraphicsContext* new_context(HWND hwnd,Surface size);
	};
}
