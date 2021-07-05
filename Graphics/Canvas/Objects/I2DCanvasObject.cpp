#include "I2DCanvasObject.h"
#include "../CanvasLayer.h"
void Canvas::I2DCanvasObject::initialize(Canvas::Canvas2DLayer* layer)
{
	_layer = layer;
	this->init();
}

Canvas::I2DCanvasObject::I2DCanvasObject()
{
	_layer = nullptr;
}

Canvas::Canvas2DLayer* Canvas::I2DCanvasObject::layer() const
{
	return _layer;
}

Render::Vertex* Canvas::I2DCanvasObject::vertices() const
{
	return _layer->vertices() + get_index();
}
