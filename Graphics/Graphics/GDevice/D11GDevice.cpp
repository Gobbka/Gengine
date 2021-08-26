#include "D11GDevice.h"
#include "../../Graphics.h"
#include "../../Render/d3d/Buffer/IndexBuffer.h"
#include "../../Render/d3d/Buffer/VertexBuffer.h"
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
	entt->assign<MeshContainerComponent>();

	return entt;
}

Render::IIndexBuffer* Render::D11GDevice::alloc_index_buffer(unsigned size)
{
	return new IndexBuffer(_gfx, new UINT[size], size);
}

Render::IIndexBuffer* Render::D11GDevice::alloc_index_buffer(void* data, unsigned size)
{
	return new IndexBuffer(_gfx, (UINT*)data, size);
}

Render::IVertexBuffer* Render::D11GDevice::alloc_vertex_buffer(unsigned size, bool dynamic)
{
	return new VertexBuffer(_gfx, new Vertex[size], size, dynamic);
}

Render::IVertexBuffer* Render::D11GDevice::alloc_vertex_buffer(void* data, unsigned size, bool dynamic)
{
	return new VertexBuffer(_gfx, (Vertex*)data, size, dynamic);
}

Render::Texture* Render::D11GDevice::create_texture(Render::Material* material)
{
	return new Texture(_gfx, *material);
}

