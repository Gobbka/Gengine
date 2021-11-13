#include "IObject.h"
#include "../Canvas.h"

void Canvas::IObject::initialize(Canvas* canvas)
{
	_canvas = canvas;
	on_initialize();
}

Render::Vertex* Canvas::IObject::vertices() const
{
	return _canvas->vertices() + get_index();
}

Canvas::Canvas* Canvas::IObject::canvas()
{
	return _canvas;
}

void Canvas::IObject::scale(float value)
{
	auto position = get_position();
	auto resolution = get_resolution();

	set_resolution({ resolution.width * value,resolution.height * value });
	
	set_position({ position.x / value,position.y / value });
}
