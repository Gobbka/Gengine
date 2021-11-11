#include "IObject.h"
#include "../Canvas.h"

void Canvas::IControllable::initialize(Canvas::Canvas* layer)
{
	_layer = layer;
	this->on_initialize();
}

Canvas::IControllable::IControllable()
{
	_layer = nullptr;
}

Canvas::Canvas* Canvas::IControllable::layer() const
{
	return _layer;
}

Render::Vertex* Canvas::IObject::vertices() const
{
	return layer()->vertices() + get_index();
}

void Canvas::IObject::scale(float value)
{
	auto position = get_position();
	auto resolution = get_resolution();

	set_resolution({ resolution.width * value,resolution.height * value });
	
	set_position({ position.x / value,position.y / value });
}
