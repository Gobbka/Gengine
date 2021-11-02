#pragma once
#include <d3d11.h>

#include "IGDevice.h"
#include "Graphics/DepthStencilStatesCollection.h"
#include "Graphics/Scene.h"
#include "Graphics/ShaderCollection.h"
#include "Render/Engine/RenderTarget.h"
#include "Render/Engine/SpriteEngine.h"
#include "Graphics/Que/IPass/Passer.h"

namespace Render {
	class IGContext;
	class RenderTarget;
	class SamplerState;
	class Camera;
}

namespace Core
{
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

		D3D11_VIEWPORT _viewport;
		Render::IGDevice* _gdevice;
		Render::IGContext* _gcontext;
	private:
		GraphicsContext(ID3D11Device*, IDXGISwapChain*, ID3D11DeviceContext*);
		
		Render::SpriteEngine* _spriteEngine;
		Render::Passer _passer;
		
	public:
		ShaderCollection shader_collection;
		Render::DepthStencilStatesCollection dss_collection;

		Render::Scene* create_scene();
		std::vector<Render::Scene*> scenes;
		Render::Scene* main_scene;
		
		Render::SpriteEngine* get_sprite_engine();
		
		Surface get_screen_resolution() const;
		inline Render::RenderTarget* get_render_target_view();

		inline Render::Passer* get_passer();
		inline Render::IGDevice* get_device();
		inline Render::IGContext* get_context();
	public:
		void set_resolution(Surface new_resolution);

		void make_frame();
		void present_frame() const;
	public:
		
		static GraphicsContext* new_context(HWND hwnd,Surface size);
	};
}
