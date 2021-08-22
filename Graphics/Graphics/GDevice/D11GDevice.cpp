#include "D11GDevice.h"
#include "../../Graphics.h"
#include "../../Render/Engine/Camera.h"

Render::D11GDevice::D11GDevice(ID3D11Device* device,Core::GraphicsContext* gfx)
{
	_device = device;
	_gfx = gfx;
}

ECS::Entity* Render::D11GDevice::create_camera(RenderTarget* target)
{
	auto entt = _gfx->worldspace()->create();
	entt->assign<Camera>(_gfx, target == nullptr ? _gfx->get_render_target_view() : target);
	
	return entt;
}

ECS::Entity* Render::D11GDevice::create_model()
{
	auto entt = _gfx->worldspace()->create();
	entt->assign<Model>();

	return entt;
}
