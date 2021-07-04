#include "CanvasLayer.h"

Canvas::CanvasLayer::CanvasLayer(Render::D3DEngine* engine)
	: _canvas(engine)
{
	
}

void Canvas::CanvasLayer::update()
{
	_canvas.update();
}

void Canvas::CanvasLayer::render(Render::DrawEvent* event)
{
	
}

Render::D3D11Canvas* Canvas::CanvasLayer::canvas()
{
	return &_canvas;
}
