#include "RenderEvent.h"
#include "../../Canvas/Objects/I2DCanvasObject.h"
#include "../Engine/D3DEngine.h"

Render::DrawEvent::DrawEvent(D3DEngine* engine, ILayer* layer)
{
	this->layer = layer;
	_engine = engine;
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
