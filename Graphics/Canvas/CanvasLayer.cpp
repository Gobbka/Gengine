#include "CanvasLayer.h"
#include "Objects/I2DCanvasObject.h"
#include "../Render/Events/RenderEvent.h"

void Canvas::Canvas2DLayer::render_components(Render::DrawEvent2D* event)
{
	for (auto* object : _objects)
		if (!object->hidden)
			event->draw_object(object);
}

Render::Vertex* Canvas::Canvas2DLayer::vertices() const
{
	return _canvas->get_ptr();
}

Canvas::Canvas2DLayer::Canvas2DLayer(Core::GraphicsContext* engine)
{
	_canvas = new Render::D3D11Canvas(engine);
	_hidden = false;
}

//Canvas::Canvas2DLayer::Canvas2DLayer(Canvas2DLayer&& other) noexcept
//{
//	_canvas = other._canvas;
//	_hidden = other._hidden;
//	_objects = other._objects;
//
//	other._canvas = nullptr;
//	other._objects.clear();
//}

Canvas::Canvas2DLayer::~Canvas2DLayer()
{
	//delete _canvas;
}

void Canvas::Canvas2DLayer::update()
{
	_canvas->update();
	
}

void Canvas::Canvas2DLayer::render(Render::DrawEvent2D* event)
{
	_canvas->bind();
	this->render_components(event);
}

Render::D3D11Canvas* Canvas::Canvas2DLayer::canvas()
{
	return _canvas;
}

void Canvas::Canvas2DLayer::add_object(I2DCanvasObject* object)
{
	object->set_index(_canvas->get_allocated_size());
	_canvas->alloc_vertexes(object->size());

	_objects.push_back(object);
	object->initialize(this);
}

