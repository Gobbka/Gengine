#include "I2DCanvasObject.h"
#include "../CanvasLayer.h"

void Canvas::IControllableObject::initialize(Canvas::Canvas2DLayer* layer)
{
	_layer = layer;
	this->init();
}

Canvas::IControllableObject::IControllableObject()
{
	_layer = nullptr;
}

Canvas::Canvas2DLayer* Canvas::IControllableObject::layer() const
{
	return _layer;
}

Render::Vertex* Canvas::I2DCanvasObject::vertices() const
{
	return layer()->vertices() + get_index();
}
