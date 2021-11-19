#include "RenderEvent.h"

#include <Graphics.h>
#include <IGContext.h>
#include <Render/Engine/Camera.h>

void Render::DrawEvent2D::mask_draw_begin() const
{
	_context->dss_collection[(DSBitSet)DepthStencilUsage::stencil_write].bind(_stencil_layer);
}

void Render::DrawEvent2D::mask_discard_begin(bool increase_layer)
{
	if (increase_layer)
		_stencil_layer++;
	
	_context->dss_collection[(DSBitSet)DepthStencilUsage::stencil_mask].bind(_stencil_layer);
}

void Render::DrawEvent2D::mask_discard_end(bool decrease_layer)
{
	if (decrease_layer)
		_stencil_layer--;

	_context->dss_collection[(DSBitSet)DepthStencilUsage::stencil_mask].bind(_stencil_layer);
}

void Render::DrawEvent2D::mask_set_stencil(BYTE new_index)
{
	_stencil_layer = new_index;
}

BYTE Render::DrawEvent2D::mask_get_stencil_layer() const
{
	return _stencil_layer;
}

void Render::DrawEvent2D::set_alpha(float alpha) const
{
	auto* context = _context->get_context();
	if(context->control_buffer.data.opacity != alpha)
	{
		context->control_buffer.data.opacity = alpha;
		context->control_buffer.update();
	}
}

Render::DrawEvent2D::DrawEvent2D(Core::GraphicsContext* ctx, Canvas::DrawData* de)
	: CanvasDrawEvent(de)
	, _context(ctx)
{}

Render::CanvasDrawEvent::CanvasDrawEvent(Canvas::DrawData* data)
	: _draw_data(data)
{}

UI::Vertex2D* Render::CanvasDrawEvent::new_draw_cmd(UINT size,Texture*texture) const
{
	texture = texture ? texture : _draw_data->default_texture;

	auto index = _draw_data->allocator.require(size);
	_draw_data->draw_list.push(Canvas::DrawCmd{ texture,0,size,index });
	
	return _draw_data->allocator.at(index);
}

void Render::CanvasDrawEvent::draw_rect(Position2 pos, Surface resolution, Color3XM color) const
{
	auto* vertices = new_draw_cmd(4);
	vertices[0] = UI::Vertex2D(pos,color,{0,0});
	vertices[1] = UI::Vertex2D({ pos.x + resolution.width,pos.y }, color, { 0,0 });
	vertices[2] = UI::Vertex2D({ pos.x,pos.y-resolution.height }, color, { 0,0 });
	vertices[3] = UI::Vertex2D({ pos.x+resolution.width,pos.y-resolution.height }, color, { 0,0 });
}

void Render::CanvasDrawEvent::draw_rect(Position2 pos, Surface resolution, Texture* texture) const
{
	const auto color = Color3XM{ 1.f,1.f,1.f,1.f };

	auto* vertices = new_draw_cmd(4,texture);
	vertices[0] = UI::Vertex2D(pos, color, { 0,0 });
	vertices[1] = UI::Vertex2D({ pos.x + resolution.width,pos.y }, color, { 1,0 });
	vertices[2] = UI::Vertex2D({ pos.x,pos.y - resolution.height }, color, { 0,1 });
	vertices[3] = UI::Vertex2D({ pos.x + resolution.width,pos.y - resolution.height }, color, { 1,1 });
}
