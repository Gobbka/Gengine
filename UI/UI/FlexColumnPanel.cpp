﻿#include "FlexColumnPanel.h"

#include "../Canvas/RenderEvent.h"
#include "Types/Types.h"

void UI::FlexColumnPanel::update_items()
{
	auto last_pos = get_position();

	for(auto*element:*children())
	{
		element->set_position(Position2{ last_pos });
		auto old_resolution = element->get_resolution();
		element->set_resolution({ get_resolution().width,old_resolution.height });

		last_pos.y -= old_resolution.height;
	}
}

void UI::FlexColumnPanel::draw(Render::DrawEvent2D* event)
{
	if (this->styles.overflow == VisibleState::hidden)
	{
		auto old_stencil = event->stencil(Render::StencilUsage::write);
		event->set_alpha(this->alpha);

		if (_texture)
			event->draw_rect(_position, _resolution, _texture);
		else
			event->draw_rect(_position, _resolution, _color);
		event->stencil_end(old_stencil);

		event->stencil(Render::StencilUsage::mask);
		event->set_alpha(1.f);
		Parent::draw(event);
		event->stencil_end(old_stencil);
	}
	else
	{
		event->set_alpha(this->alpha);

		if (_texture)
			event->draw_rect(_position, _resolution, _texture);
		else
			event->draw_rect(_position, _resolution, _color);

		event->set_alpha(1.f);
		Parent::draw(event);
	}
}

UI::ElementDescription UI::FlexColumnPanel::get_desc()
{
	return ElementDescription(true, "FLEXCOLUMNPANEL");
}

UI::FlexColumnPanel::FlexColumnPanel(Vector2 position, Surface resolution, Render::GETexture* texture)
	: Parent(position)
	, _position(position)
	, _resolution(resolution)
	, _texture(texture)
	, _color(1, 1, 1)
{}

UI::FlexColumnPanel::FlexColumnPanel(Vector2 position, Surface resolution, Color3XM color)
	: Parent(position)
	, _position(position)
	, _resolution(resolution)
	, _texture(nullptr)
	, _color(color)
{}

bool UI::FlexColumnPanel::point_belongs(Position2 point)
{
	auto resolution = _resolution;
	auto position = _position;

	return
		(point.x >= position.x && point.x <= position.x + resolution.width) &&
		(point.y <= position.y && point.y >= (position.y - resolution.height));
}

void UI::FlexColumnPanel::set_position(Position2 pos)
{
	move_by(pos - _position);

	_position = pos;
}

void UI::FlexColumnPanel::move_by(Position2 pos)
{
	_position += pos;

	Parent::move_by(pos);
}

void UI::FlexColumnPanel::set_texture(Render::GETexture* texture)
{
	_texture = texture;
}

Position2 UI::FlexColumnPanel::get_position()
{
	return _position;
}


Surface UI::FlexColumnPanel::get_resolution()
{
	return _resolution;
}

void UI::FlexColumnPanel::set_resolution(Surface surface)
{
	_resolution = surface;
}
