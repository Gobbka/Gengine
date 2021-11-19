#include "IObject.h"
#include "../CanvasImpl.h"

void Canvas::IObject::initialize(CanvasImpl* canvas)
{
	_canvas = canvas;
	on_initialize();
}

UI::Vertex2D* Canvas::IObject::vertices() const
{
	return _canvas->vertices() + get_index();
}

Canvas::CanvasImpl* Canvas::IObject::canvas() const
{
	return _canvas;
}
