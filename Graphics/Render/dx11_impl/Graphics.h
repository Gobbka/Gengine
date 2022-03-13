 #pragma once
#include <d3d11.h>

#include "../Common/IAllocator.h"
#include "../../Graphics/DepthStencilStatesCollection.h"
#include "../../Graphics/Scene.h"
#include "../../Graphics/ShaderCollection.h"
#include "../Common/RenderTarget.h"
#include "../Common/SpriteEngine.h"
#include "../../Graphics/Commander.h"

namespace Render
{
	class __declspec(dllexport) DX11Graphics final
	{
	public:
		ID3D11DeviceContext* context;
		ID3D11Device* device;
	private:
		Surface _screen_resolution;
		
		IDXGISwapChain* _swap;
		DX11RenderTarget _targetView;

		GESamplerState* _samplerState;

		IAllocator* _gdevice;
		IGContext* _gcontext;
	private:
		
		SpriteEngine* _spriteEngine;
	public:
		DX11Graphics(ID3D11Device*, IDXGISwapChain*, ID3D11DeviceContext*);
		~DX11Graphics();

		ShaderCollection shader_collection;
		DepthStencilStatesCollection dss_collection;
		Commander* commander;

		Scene* create_empty_scene();
		Scene* create_scene_3d();
		std::vector<Scene*> scenes;
		Scene* main_scene;
		
		SpriteEngine* get_sprite_engine() const;
		
		Surface get_screen_resolution() const;
		inline GERenderTarget* get_render_target_view();

		inline IAllocator* get_device() const;
		inline IGContext* get_context() const;
	public:
		void set_resolution(Surface new_resolution);

		void make_frame();
		void present_frame() const;
	};
}

__declspec(dllexport) Render::GEGraphics* Graphics_CreateContext(HWND hwnd);
