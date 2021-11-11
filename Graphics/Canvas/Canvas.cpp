#include "Canvas.h"
#include "Objects/IObject.h"
#include "../Render/Events/RenderEvent.h"

void Canvas::Canvas::render_components(Render::DrawEvent2D* event)
{
	for (auto* object : _objects)
		if (!object->hidden)
			event->draw_object(object);
}

Render::Vertex* Canvas::Canvas::vertices() const
{
	return _canvas.get_ptr();
}

Canvas::Canvas::Canvas(Core::GraphicsContext* engine)
	: _canvas(engine)
{
	_hidden = false;
}

Canvas::Canvas::~Canvas()
{
}

void Canvas::Canvas::update() const
{
	_canvas.update();
}

void Canvas::Canvas::render(Render::DrawEvent2D* event)
{
	_canvas.bind();
	this->render_components(event);
}

void Canvas::Canvas::add_object(IObject* object)
{
	object->set_index(_canvas.last_index());
	_canvas.alloc(object->size());

	_objects.push_back(object);
	object->initialize(this);
}
