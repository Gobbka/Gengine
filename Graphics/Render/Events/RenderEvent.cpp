#include "RenderEvent.h"
#include "../../Canvas/Objects/I2DCanvasObject.h"
#include "../Engine/D3DEngine.h"
#include "../Engine/MaskEngine.h"

Render::DrawEvent::DrawEvent(D3DEngine* engine, ILayer* layer)
{
	this->layer = layer;
	_engine = engine;
}

void Render::DrawEvent::mask_draw_begin() const
{
	auto* mask = _engine->mask_engine();
	mask->set_state(mask->get_drawState(), _stencil_layer);
}

void Render::DrawEvent::mask_discard_begin(bool increase_layer)
{
	if (increase_layer)
		this->_stencil_layer++;
	auto* mask = _engine->mask_engine();
	mask->set_state(mask->get_discardState(), _stencil_layer);
}

void Render::DrawEvent::mask_discard_end(bool decrease_layer)
{
	if (decrease_layer)
		this->_stencil_layer--;
	auto* mask = _engine->mask_engine();
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
	_engine->mask_engine()->clear_buffer();
}

void Render::DrawEvent::set_alpha(float alpha)
{
	_engine->set_alpha(alpha);
}

void Render::DrawEvent::draw_vertex(UINT count, UINT start) const
{
	_engine->context()->Draw(count, start + _draw_index);
}

void Render::DrawEvent::draw_object(Canvas::I2DCanvasObject* object)
{
	_draw_index = object->get_index();
	object->draw(this);
}
