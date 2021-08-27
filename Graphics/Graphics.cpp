#include "Graphics.h"

#include <d3dcompiler.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"D3DCompiler.lib")

#include "Ecs/Ecs.h"
#include "Graphics/GDevice/D11GContext.h"
#include "Graphics/GDevice/D11GDevice.h"
#include "Types/Types.h"
#include "Render/Engine/Camera.h"

#include "Render/d3d/Shader/SamplerState.h"
#include "Render/d3d/Shader/PixelShader.h"
#include "Render/d3d/Shader/VertexShader.h"

#include "Graphics/Que/IPass/IPass.h"
#include "Graphics/Que/RenderQueuePass/RenderQueuePass.h"

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

	_samplerState = new Render::SamplerState(this);
	
	_pixelShader  = new Render::PixelShader(this);

	auto* _phong_ps = new Render::PixelShader(this);
	auto* _texture_ps = new Render::PixelShader(this);
	
	auto* _texture_vs = new Render::VertexShader(this);

	ID3D11InputLayout* _texture_layout=nullptr;

	_pixelShader->read_file(L"d3d11\\pixel_shader.cso");
	_pixelShader->release_blob();

	_texture_vs->read_file(L"d3d11\\texture_vs.cso");
	_texture_vs->create_input_layout(Render::VertexLayout, ARRAYSIZE(Render::VertexLayout), &_inputLayout);
	_texture_vs->release_blob();

	_phong_ps->read_file(L"d3d11\\phong_ps.cso");
	_phong_ps->release_blob();

	_texture_ps->read_file(L"d3d11\\texture_ps.cso");
	_texture_ps->release_blob();

	_spriteEngine = new Render::SpriteEngine(
		this,
		_texture_ps,_phong_ps,_pixelShader,_texture_vs,_inputLayout
	);

	context->IASetInputLayout(_inputLayout);

	_gdevice = new Render::D11GDevice(device, this);
	_gcontext = new Render::D11GContext(this,context);

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
	context->RSSetViewports(1, &_viewport);
	_gcontext->set_topology(Render::PrimitiveTopology::TRIANGLESTRIP);

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

void Core::GraphicsContext::present_frame()
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
