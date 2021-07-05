#include "CanvasLayer.h"
#include "Objects/I2DCanvasObject.h"
#include "../Render/d3d/Buffer/VertexBuffer.h"

Render::Vertex* Canvas::Canvas2DLayer::vertices() const
{
	return _canvas.get_ptr();
}

Canvas::Canvas2DLayer::Canvas2DLayer(Render::D3DEngine* engine)
	: _canvas(engine)
{
	
}

void Canvas::Canvas2DLayer::update()
{
	_canvas.update();
}

void Canvas::Canvas2DLayer::render(Render::DrawEvent* event)
{	
	for(auto object : _objects)
	{
		if(!object->hidden)
			object->draw(event);
	}
}

Render::D3D11Canvas* Canvas::Canvas2DLayer::canvas()
{
	return &_canvas;
}

void Canvas::Canvas2DLayer::add_object(I2DCanvasObject* object)
{
	object->set_index(_canvas.get_allocated_size());
	_canvas.alloc_vertexes(object->size());

	_objects.push_back(object);
	object->initialize(this);
}

