#include "Graphics.h"

#include <d3dcompiler.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"D3DCompiler.lib")

#include "Graphics/GDevice/D11GContext.h"
#include "Graphics/GDevice/D11GDevice.h"
#include "Graphics/Que/CreateShadowmapPass/CreateShadowMapPass.h"
#include "Types/Types.h"

#include "Render/d3d/Shader/SamplerState.h"
#include "Render/d3d/Shader/VertexShader.h"

#include "Graphics/Que/RenderQueuePass/RenderMeshPass.h"
#include "Render/d3d/Vertex.h"
#include "Render/Engine/RenderTarget.h"
#include "Render/Engine/SpriteEngine.h"

Core::GraphicsContext::GraphicsContext(ID3D11Device* dev, IDXGISwapChain* swap, ID3D11DeviceContext* context)
	: context(context),
	device(dev),
	_screen_resolution(0,0),
	shader_collection(this),
	_targetView(this,swap)
{
	_swap = swap;

	_gdevice = new Render::D11GDevice(dev, this);
	_gcontext = new Render::D11GContext(this, context);

	{
		DXGI_SWAP_CHAIN_DESC desc;
		swap->GetDesc(&desc);
		_screen_resolution = Surface(desc.BufferDesc.Width,desc.BufferDesc.Height);
	}

	_samplerState = new Render::SamplerState(this);
	
	auto* _texture_vs = new Render::VertexShader(this);
	_texture_vs->read_file(L"d3d11\\texture_vs.cso");
	_texture_vs->create_input_layout(Render::VertexLayout, ARRAYSIZE(Render::VertexLayout), &_inputLayout);
	_texture_vs->release_blob();
	shader_collection.insert(L"d3d11\\texture_vs.cso", _texture_vs);

	_spriteEngine = new Render::SpriteEngine(
		this
	);

	_gcontext->set_vertex_shader(_texture_vs);

	context->IASetInputLayout(_inputLayout);

	_passer._begin_passes.push_back(new Render::ClearPass());
	_passer._probe_passes.push_back(new Render::CreateShadowMapPass());
	_passer._end_passes.push_back(new Render::RenderMeshPass(this));

	_gcontext->set_topology(PrimitiveTopology::TRIANGLESTRIP);
	
	_viewport.Width  = _screen_resolution.width;
	_viewport.Height = _screen_resolution.height;
	_viewport.MaxDepth = 1;
	_viewport.MinDepth = 0;
	_viewport.TopLeftX = 0;
	_viewport.TopLeftY = 0;
	context->RSSetViewports(1, &_viewport);

	_samplerState->bind();
}

Render::Scene* Core::GraphicsContext::create_scene()
{
	auto* scene = new Render::Scene(this);
	this->scenes.push_back(scene);
	if (main_scene == nullptr)
		main_scene = scene;
	return scene;
}

Render::SpriteEngine* Core::GraphicsContext::get_sprite_engine()
{
	return _spriteEngine;
}

Surface Core::GraphicsContext::get_screen_resolution() const
{
	return _screen_resolution;
}

inline Render::RenderTarget* Core::GraphicsContext::get_render_target_view()
{
	return &_targetView;
}

inline Render::Passer* Core::GraphicsContext::get_passer()
{
	return &_passer;
}

inline Render::IGDevice* Core::GraphicsContext::get_device()
{
	return _gdevice;
}

inline Render::IGContext* Core::GraphicsContext::get_context()
{
	return _gcontext;
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
	if (_viewport.Width == 0.f || _viewport.Height == 0.f)
		return;

	context->RSSetViewports(1, &_viewport);

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

	for (Render::IPass* pass : _passer._overlay_passes)
	{
		pass->execute(this);
	}
}

void Core::GraphicsContext::present_frame() const
{
	_swap->Present(1u, 0u);
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
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
#ifdef _DEBUG 
		D3D11_CREATE_DEVICE_DEBUG 
#else 
		0 
#endif
		,
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
