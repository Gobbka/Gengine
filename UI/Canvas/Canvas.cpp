#include "Canvas.h"
#include "Objects/IObject.h"
#include "RenderEvent.h"

UI::Vertex2D* Canvas::Canvas::vertices() const
{
	return _canvas.get_ptr();
}

Canvas::Canvas::Canvas(Core::GraphicsContext* engine)
	: _canvas(engine)
{}

void Canvas::Canvas::update() const
{
	_canvas.update();
}

void Canvas::Canvas::render(Render::DrawEvent2D* event)
{
	bind();
	for (auto* object : _objects)
		if (!object->hidden)
			event->draw_object(object);
}

void Canvas::Canvas::add_object(IObject* object)
{
	object->set_index(_canvas.last_index());
	_canvas.alloc(object->size());

	_objects.push_back(object);
	object->initialize(this);
}

void Canvas::Canvas::bind() const
{
	_canvas.bind();
}

