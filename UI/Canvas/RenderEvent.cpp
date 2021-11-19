#include "RenderEvent.h"

#include "Objects/IObject.h"
#include <Graphics.h>
#include <IGContext.h>
#include <Render/Engine/Camera.h>

Render::SpriteEngine* Render::DrawEvent2D::sprite_engine() const
{
	return _spriteEngine;
}

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
	auto* mask = _camera->get_mask_engine();
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

void Render::DrawEvent2D::mask_clear() const
{
	_camera->get_mask_engine()->clear_buffer();
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

UI::Vertex2D* Render::DrawEvent2D::draw(UINT vertices_count)
{


	return nullptr;
}

void Render::DrawEvent2D::draw_vertex(UINT count, UINT start) const
{
	_context->context->Draw(count, start + _draw_index);
}

void Render::DrawEvent2D::draw_object(Canvas::IObject* object)
{
	_draw_index = object->get_index();
	object->draw(this);
}

Render::CanvasDrawEvent::CanvasDrawEvent(Canvas::DrawData* data)
{
	_draw_data = data;
}

UI::Vertex2D* Render::CanvasDrawEvent::new_draw_cmd(UINT size)
{
	_draw_data->draw_list.push_back(Canvas::DrawCmd{});
	return nullptr;
}

void Render::CanvasDrawEvent::draw_rect(Position2 pos, Surface resolution, Color3XM color)
{
	auto* vertices = new_draw_cmd(4);
	vertices[0] = UI::Vertex2D{};
}


Render::DrawEvent2D::DrawEvent2D(Camera* camera, Canvas::CanvasImpl* layer)
{
	this->layer = layer;
	_camera = camera;
	_context = _camera->graphics_context();
	_spriteEngine = _context->get_sprite_engine();
}
