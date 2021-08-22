#include "Graphics.h"

#include <d3dcompiler.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"D3DCompiler.lib")

#include <iostream>

#include "Canvas/CanvasLayer.h"
#include "Ecs/Ecs.h"
#include "Types/Types.h"
#include "Render/d3d/Buffer/Texture.h"
#include "Render/Engine/Camera.h"

#include "Render/d3d/Shader/SamplerState.h"
#include "Render/d3d/Shader/PixelShader.h"
#include "Render/d3d/Shader/VertexShader.h"

#include "Graphics/Material/Material.h"
#include "Graphics/Que/IPass/IPass.h"
#include "Graphics/Que/RenderQueuePass/RenderQueuePass.h"
#include "Render/d3d/Buffer/D3D11BufferAllocator.h"

void Core::WorldSpace::add_object(Render::Model* object)
{
	objects.push_back(object);
}

Core::GraphicsContext::GraphicsContext(ID3D11Device* dev, IDXGISwapChain* swap, ID3D11DeviceContext* context)
	: context(context),
	device(dev),
	_screen_resolution(0,0),
	_targetView(this,swap),
	_shadowRenderTarget(this,Render::RenderTargetUsage::null),
	pixel_shader(this)
{
	_swap = swap;

	{
		DXGI_SWAP_CHAIN_DESC desc;
		swap->GetDesc(&desc);
		_screen_resolution = Surface(desc.BufferDesc.Width,desc.BufferDesc.Height);
	}

	_shadowRenderTarget = Render::RenderTarget(this, _screen_resolution);

	_bufferAllocator = new Render::D3D11BufferAllocator(this);

	_samplerState = new Render::SamplerState(this);
	
	_pixelShader  = new Render::PixelShader(this);

	auto* _texture_ps = new Render::PixelShader(this);
	auto* _texture_vs = new Render::VertexShader(this);

	ID3D11InputLayout* _texture_layout=nullptr;

	_pixelShader->read_file(L"d3d11\\pixel_shader.cso");
	_pixelShader->release_blob();

	_texture_vs->read_file(L"d3d11\\texture_vs.cso");
	_texture_vs->create_input_layout(Render::VertexLayout, ARRAYSIZE(Render::VertexLayout), &_inputLayout);
	_texture_vs->release_blob();

	_texture_ps->read_file(L"d3d11\\texture_ps.cso");
	_texture_ps->release_blob();

	_spriteEngine = new Render::SpriteEngine(
		this, 
		_texture_ps, _texture_vs, _inputLayout,
		_pixelShader,_texture_vs,_inputLayout
	);

	_worldSpace = ECS::World::createWorld();

	context->IASetInputLayout(_inputLayout);

	_passer._begin_passes.push_back(new Render::ClearPass());
	_passer._end_passes.push_back(new Render::RenderQueuePass(this));
	
	_viewport.Width  = _screen_resolution.width;
	_viewport.Height = _screen_resolution.height;
	_viewport.MaxDepth = 1;
	_viewport.MinDepth = 0;
	_viewport.TopLeftX = 0;
	_viewport.TopLeftY = 0;
	context->RSSetViewports(1, &_viewport);

	_samplerState->bind();
}

Render::IBufferAllocator* Core::GraphicsContext::buffer_allocator() const
{
	return _bufferAllocator;
}

ECS::World* Core::GraphicsContext::worldspace()
{
	return _worldSpace;
}

Render::SpriteEngine* Core::GraphicsContext::get_sprite_engine()
{
	return _spriteEngine;
}

Surface Core::GraphicsContext::get_screen_resolution() const
{
	return _screen_resolution;
}

Render::RenderTarget* Core::GraphicsContext::get_render_target_view()
{
	return &_targetView;
}

Render::RenderTarget* Core::GraphicsContext::get_shadow_render_target()
{
	return &_shadowRenderTarget;
}

ECS::Entity* Core::GraphicsContext::create_camera(Render::RenderTarget* target)
{
	auto entt = _worldSpace->create();
	entt->assign<Render::Camera>(this, target == nullptr ? &_targetView : target);
	return entt;
}

ECS::Entity* Core::GraphicsContext::create_model()
{
	auto entt = _worldSpace->create();
	entt->assign<Render::Model>();
	return entt;
}

void Core::GraphicsContext::bind_main_camera(ECS::Entity* ent)
{
	_main_camera = ent;
}

ECS::Entity* Core::GraphicsContext::get_main_camera()
{
	return _main_camera;
}

void Core::GraphicsContext::set_resolution(Surface new_resolution)
{
	_screen_resolution = new_resolution;

	_viewport.Width = _screen_resolution.width;
	_viewport.Height = _screen_resolution.height;
}

void Core::GraphicsContext::make_frame()
{
	// begin passes
	context->RSSetViewports(1, &_viewport);
	context->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	for (Render::IPass* pass : _passer._begin_passes)
	{
		pass->execute(this);
	}
	
	// probe,update,collection pass
	for(Render::IPass*pass :_passer._probe_passes)
	{
		pass->execute(this);
	}

	// render pass
	for (Render::IPass* pass : _passer._draw_passes)
	{
		pass->execute(this);
	}

	for (Render::IPass* pass : _passer._end_passes)
	{
		pass->execute(this);
	}
}

void Core::GraphicsContext::present_frame()
{
	_swap->Present(1u, 0u);
}

Render::Texture* Core::GraphicsContext::create_texture(Render::Material* material)
{
	return new Render::Texture(this, *material);
}

Core::GraphicsContext* Core::GraphicsContext::new_context(HWND hwnd,Surface size)
{
	IDXGISwapChain* pswap=nullptr;
	ID3D11Device* device=nullptr;
	ID3D11DeviceContext* context=nullptr;

	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc = DXGI_MODE_DESC{
		(UINT)size.width,(UINT)size.height,
		{60,1},
		DXGI_FORMAT_B8G8R8A8_UNORM,
		DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,
		DXGI_MODE_SCALING_UNSPECIFIED
	};
	sd.SampleDesc = { 1,0 };
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hwnd;
	sd.BufferCount = 1;
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;
	
	auto hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
	#ifdef _DEBUG
		//D3D_DRIVER_TYPE_REFERENCE,
		D3D_DRIVER_TYPE_HARDWARE,
	#else
		D3D_DRIVER_TYPE_HARDWARE,
	#endif
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&pswap,
		&device,
		nullptr,
		&context
	);
	
	assert(SUCCEEDED(hr));

	return new GraphicsContext(device, pswap, context);
}
