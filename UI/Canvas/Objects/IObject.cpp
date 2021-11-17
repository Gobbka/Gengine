#include "IObject.h"
#include "../Canvas.h"

void Canvas::IObject::initialize(Canvas* canvas)
{
	_canvas = canvas;
	on_initialize();
}

UI::Vertex2D* Canvas::IObject::vertices() const
{
	return _canvas->vertices() + get_index();
}

Canvas::Canvas* Canvas::IObject::canvas() const
{
	return _canvas;
}
