#include "Commander.h"

#include "Camera.h"
#include "DepthStencilStatesCollection.h"
#include "Mesh.h"
#include "../Render/Common/Graphics.h"
#include "../Render/Common/IGContext.h"
#include "../Render/Common/IndexBuffer.h"

Render::Commander::Commander(GEGraphics* gfx)
	: _gfx(gfx)
	, _normals_ps(_gfx->shader_collection.get<PixelShader>(L"d3d11\\normals_ps.cso"))
	, _normals_texture_ps(_gfx->shader_collection.get<PixelShader>(L"d3d11\\normals_texture_ps.cso"))
{
}

void Render::Commander::nm_begin()
{
	_gfx->dss_collection[(DSBitSet)DepthStencilUsage::depth].bind();
}

void Render::Commander::nm_solid_mode()
{
	_gfx->get_context()->set_pixel_shader(_normals_ps);
}

void Render::Commander::nm_texture_mode(GETexture* normals)
{
	_gfx->get_context()->set_pixel_shader(_normals_texture_ps);
	_gfx->get_sprite_engine()->bind_texture(normals, 0);
}

void Render::Commander::draw_mesh(Mesh& mesh)
{
	auto* gcontext = _gfx->get_context();

	mesh.index_buffer->bind();
	mesh.buffer->bind();
	gcontext->set_topology(mesh.topology);

	gcontext->draw_indexed(mesh.index_buffer->get_size());
}
