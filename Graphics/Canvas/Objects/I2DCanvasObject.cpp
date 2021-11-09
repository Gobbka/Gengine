#include "I2DCanvasObject.h"
#include "../CanvasComponent.h"

void Canvas::IControllableObject::initialize(Canvas::CanvasComponent* layer)
{
	_layer = layer;
	this->on_initialize();
}

Canvas::IControllableObject::IControllableObject()
{
	_layer = nullptr;
}

Canvas::CanvasComponent* Canvas::IControllableObject::layer() const
{
	return _layer;
}

Render::Vertex* Canvas::I2DCanvasObject::vertices() const
{
	return layer()->vertices() + get_index();
}

void Canvas::I2DCanvasObject::scale(float value)
{
	auto position = get_position();
	auto resolution = get_resolution();

	set_resolution({ resolution.width * value,resolution.height * value });
	
	set_position({ position.x / value,position.y / value });
}
