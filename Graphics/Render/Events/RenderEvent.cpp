#include "RenderEvent.h"
#include "../../Canvas/Objects/I2DCanvasObject.h"
#include "../Engine/Camera.h"
#include "../Engine/MaskEngine.h"

Render::DrawEvent::DrawEvent(Camera* engine)
{
	_camera = engine;
}

Render::SpriteEngine* Render::DrawEvent::sprite_engine()
{
	return _camera->graphics_context()->get_sprite_engine();
}

void Render::DrawEvent::mask_draw_begin() const
{
	auto* mask = _camera->mask_engine();
	mask->set_state(mask->get_drawState(), _stencil_layer);
}

void Render::DrawEvent::mask_discard_begin(bool increase_layer)
{
	if (increase_layer)
		this->_stencil_layer++;
	auto* mask = _camera->mask_engine();
	mask->set_state(mask->get_discardState(), _stencil_layer);
}

void Render::DrawEvent::mask_discard_end(bool decrease_layer)
{
	if (decrease_layer)
		this->_stencil_layer--;
	auto* mask = _camera->mask_engine();
	mask->set_state(mask->get_discardState(), _stencil_layer);
}

void Render::DrawEvent::mask_set_stencil(BYTE new_index)
{
	_stencil_layer = new_index;
}

BYTE Render::DrawEvent::mask_get_stencil_layer()
{
	return _stencil_layer;
}

void Render::DrawEvent::mask_clear()
{
	_camera->mask_engine()->clear_buffer();
}

void Render::DrawEvent::set_alpha(float alpha)
{
	_camera->set_alpha(alpha);
}

void Render::DrawEvent2D::draw_vertex(UINT count, UINT start) const
{
	_camera->context()->Draw(count, start + _draw_index);
}

void Render::DrawEvent2D::draw_object(Canvas::I2DCanvasObject* object)
{
	_draw_index = object->get_index();
	object->draw(this);
}

Render::DrawEvent3D::DrawEvent3D(Camera* camera)
	: DrawEvent(camera)
{
	
}

void Render::DrawEvent3D::draw_object(I3DObject* object)
{
	object->transform.get_world_matrix();
}

Render::DrawEvent2D::DrawEvent2D(Camera* camera, ILayer* layer)
	: DrawEvent(camera)
{
	this->layer = layer;
}
