#include "Rectangle.h"
#include "../../../Render/Events/RenderEvent.h"
#include "../../../Render/d3d/Vertex.h"

Canvas::I2DCanvasObject::INDEX Canvas::Rectangle::size()
{
	return 4;
}

void Canvas::Rectangle::apply_rectangle()
{
	auto* ptr = vertices();

	auto x = _position.x;
	auto y = _position.y;
	auto width = _resolution.width;
	auto height = _resolution.height;
	
	ptr[0].pos = DirectX::XMFLOAT3(x, y, 1.f);
	ptr[1].pos = DirectX::XMFLOAT3(x + width, y, 1.f);
	ptr[2].pos = DirectX::XMFLOAT3(x, y - height, 1.f);
	ptr[3].pos = DirectX::XMFLOAT3(x + width, y - height, 1.f);
}

void Canvas::Rectangle::on_initialize()
{
	this->set_position(_position);
	this->set_resolution(_resolution);
	this->set_color(_background_color);
}

Canvas::Rectangle::Rectangle(Color4 background, Position2 position, Surface resolution)
	: _background_color(background),
	_position(position),
	_resolution(resolution)
{
	
}


void Canvas::Rectangle::draw(Render::DrawEvent* draw_event)
{
	draw_event->draw_vertex(4);
}

void Canvas::Rectangle::set_position(Position2 pos)
{
	_position = pos;
	
	if (this->layer() == nullptr)
		return;
	apply_rectangle();
}

Position2 Canvas::Rectangle::get_position()
{
	return _position;
}

void Canvas::Rectangle::set_resolution(Surface surface)
{
	_resolution = surface;

	if (this->layer() == nullptr)
		return;
	apply_rectangle();
}

Surface Canvas::Rectangle::get_resolution()
{
	return _resolution;
}

void Canvas::Rectangle::move_by(Position2 pos)
{
	_position += pos;

	if (this->layer() == nullptr)
		return;
	
	auto* ptr = vertices();

	for (INDEX i = 0; i < size(); i++)
	{
		const auto _pos = ptr[i].pos;
		ptr[i].pos = DirectX::XMFLOAT3(_pos.x + pos.x, _pos.y + pos.y, 1.f);
	}
}

void Canvas::Rectangle::set_color(Color4 color)
{
	_background_color = color;
	
	if (this->layer() == nullptr)
		return;

	for(INDEX i = 0;i < size();i++)
		vertices()[i].color = color.to_float3();
}

Color4 Canvas::Rectangle::get_color()
{
	return _background_color;
}

void Canvas::Rectangle::set_texture(Render::Texture* texture)
{
	auto* ptr = vertices();
	ptr[0].color = { 0,0,0 };
	ptr[1].color = { 1,0,0 };
	ptr[2].color = { 0,1,0 };
	ptr[3].color = { 1,1,0 };
}
