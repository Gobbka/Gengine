#include "Graphics.h"

#include "Graphics/GDevice/D11GContext.h"
#include "Graphics/GDevice/D11GDevice.h"
#include "Graphics/Que/CreateLightMapPass/CreateLightMapPass.h"
#include "Graphics/Que/CreateNormalsMapPass/CreateNormalsmapPass.h"
#include "Graphics/Que/DrawSkyboxPass/DrawSkyboxPass.h"
#include "Types/Types.h"

#include "Render/d3d/Shader/SamplerState.h"
#include "Render/d3d/Shader/VertexShader.h"

#include "Graphics/Que/RenderQueuePass/RenderMeshPass.h"
#include "Render/d3d/Vertex.h"
#include "Render/Engine/RenderTarget.h"
#include "Render/Engine/SpriteEngine.h"

#include "GraphicsBuildSettings.h"
#include "Logger/Logger.h"

Core::GraphicsContext::GraphicsContext(ID3D11Device* dev, IDXGISwapChain* swap, ID3D11DeviceContext* context)
	: context(context)
	, device(dev)
	, _screen_resolution(0,0)
	, _swap(swap)
	, _targetView(this,swap)
	, _samplerState(new Render::SamplerState(this))
	, _gdevice(new Render::D11GDevice(dev,this))
	, _gcontext(new Render::D11GContext(context,this))
	, _spriteEngine(new Render::SpriteEngine(this))
	, shader_collection(this)
	, dss_collection(this)
	, main_scene(nullptr)
{
	set_resolution(_targetView.get_texture()->resolution());
	
	auto* texture_vs = new Render::VertexShader(this, L"d3d11\\texture_vs.cso",Render::VertexLayout,ARRAYSIZE(Render::VertexLayout));

	shader_collection.insert(L"d3d11\\texture_vs.cso", texture_vs);

	_gcontext->set_vertex_shader(texture_vs);

	_gcontext->set_topology(PrimitiveTopology::TRIANGLESTRIP);

	_samplerState->bind();
}

Core::GraphicsContext::~GraphicsContext()
{
	if (device)
		device->Release();
	if (context)
		context->Release();
	if (_swap)
		_swap->Release();

	delete _samplerState;
	delete _gdevice;
	delete _gcontext;
	delete _spriteEngine;

	for(const auto*scene:scenes)
	{
		scene->world()->destroyWorld();
	}
}

Render::Scene* Core::GraphicsContext::create_empty_scene()
{
	auto* scene = new Render::Scene(this);
	this->scenes.push_back(scene);
	if (main_scene == nullptr)
		main_scene = scene;
	return scene;
}

Render::Scene* Core::GraphicsContext::create_scene_3d()
{
	auto* scene = create_empty_scene();
	auto &pipeline = scene->render_pipeline();

	pipeline.add_pass(new Render::ClearPass(this), Render::PassStep::begin);
	pipeline.add_pass(new Render::DrawSkyboxPass(this), Render::PassStep::begin);
	//_passer._probe_passes.push_back(new Render::CreateShadowMapPass());
	pipeline.add_pass(new Render::CreateNormalsMapPass(this), Render::PassStep::probe);
	//_passer.add_pass(new Render::CreateLightMapPass(this),Render::PassStep::probe);
	pipeline.add_pass(new Render::RenderMeshPass(this), Render::PassStep::draw);

	return scene;
}

Render::SpriteEngine* Core::GraphicsContext::get_sprite_engine() const
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

inline Render::IGDevice* Core::GraphicsContext::get_device() const
{
	return _gdevice;
}

inline Render::IGContext* Core::GraphicsContext::get_context() const
{
	return _gcontext;
}

void Core::GraphicsContext::set_resolution(Surface new_resolution)
{
	_screen_resolution = new_resolution;

	const CD3D11_VIEWPORT viewport{ 0.f,0.f,_screen_resolution.width,_screen_resolution.height };
	context->RSSetViewports(1, &viewport);
}

void Core::GraphicsContext::make_frame()
{
	if (_screen_resolution.width == 0.f || _screen_resolution.height == 0.f)
		return;

	for (auto* scene : scenes) {

		if (!scene->active || scene == main_scene)
			continue;

		scene->render_pipeline().execute(scene);
	}

	main_scene->render_pipeline().execute(main_scene);
}

void Core::GraphicsContext::present_frame() const
{
	_swap->Present(1u, 0u);
}

Core::GraphicsContext* Graphics_CreateContext(HWND hwnd)
{
#ifdef DRAW_LIBRARY_DX11
	IDXGISwapChain* pswap = nullptr;
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* context = nullptr;
	RECT screen_resolution;

	GetClientRect(hwnd, &screen_resolution);

	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc = DXGI_MODE_DESC{
		(UINT)screen_resolution.left,(UINT)screen_resolution.bottom,
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

	const auto hr = D3D11CreateDeviceAndSwapChain(
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

	GEAssert(hr).abort(TEXT("Graphics.cpp: cannot create dx11 device and swap chain"));

	return new Core::GraphicsContext(device, pswap, context);
#endif
}
