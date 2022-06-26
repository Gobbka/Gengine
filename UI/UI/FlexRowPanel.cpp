#include "FlexRowPanel.h"

#include "../Canvas/RenderEvent.h"
#include "Types/Types.h"

void UI::FlexRowPanel::update_items()
{
	_location_rule.place_on(get_position(), get_resolution());
}

void UI::FlexRowPanel::draw(Render::DrawEvent2D* event)
{
	auto old_stencil = event->stencil(Render::StencilUsage::write);
	event->set_alpha(styles.alpha);

	if (_texture)
		event->drawRect(_position, _resolution, _texture);
	else
		event->drawRect(_position, _resolution, _color);

	event->stencil(Render::StencilUsage::mask);
	event->set_alpha(1.f);
	Parent::draw(event);
	const auto height_ratio = _location_rule.height_ratio();

	if (height_ratio < 1)
	{
		auto resolution = get_resolution();
		auto position = get_position();
		// scroll bar width
		constexpr auto sb_width = 20;
		// scroll bar height
		const auto sb_height = resolution.height * height_ratio - 10;

		event->drawRect(
			{ position.x + resolution.width - sb_width - 5,position.y - _scroll_offset.y * height_ratio - 5},
			{ sb_width,sb_height },
			Color3XM::from_rgb(62, 62, 62)
		);
	}

	event->stencilEnd(old_stencil);
	event->stencilEnd(old_stencil);
}

UI::ElementDescription UI::FlexRowPanel::get_desc()
{
	return ElementDescription(true, "FLEXROWPANEL");
}

UI::FlexRowPanel::FlexRowPanel(Vector2 position, Surface resolution, Render::GETexture* texture)
	: Parent(position)
	, _position(position)
	, _resolution(resolution)
	, _texture(texture)
	, _color(1, 1, 1)
	, _scroll_offset(0, 0)
	, _location_rule(children())
{
}

UI::FlexRowPanel::FlexRowPanel(Vector2 position, Surface resolution, Color3XM color)
	: Parent(position)
	, _position(position)
	, _resolution(resolution)
	, _texture(nullptr)
	, _color(color)
	, _scroll_offset(0,0)
	, _location_rule(children())
{
}

UI::FlexRowPanel::~FlexRowPanel()
{
}

bool UI::FlexRowPanel::point_belongs(Position2 point)
{
	auto resolution = _resolution;
	auto position = _position;

	return
		(point.x >= position.x && point.x <= position.x + resolution.width) &&
		(point.y <= position.y && point.y >= (position.y - resolution.height));
}

void UI::FlexRowPanel::set_position(Position2 pos)
{
	_position = pos;
}

void UI::FlexRowPanel::move_by(Position2 pos)
{
	_position += pos;

	Parent::move_by(pos);
}

void UI::FlexRowPanel::set_texture(Render::GETexture* texture)
{
	_texture = texture;
}

Position2 UI::FlexRowPanel::get_position()
{
	return _position;
}


Surface UI::FlexRowPanel::get_resolution()
{
	return _resolution;
}

void UI::FlexRowPanel::set_resolution(Surface surface)
{
	_resolution = surface;
}

void UI::FlexRowPanel::handle_mouse_scroll(int delta)
{
	const auto height_ratio = _location_rule.height_ratio();
	if(height_ratio >= 1)
	{
		return;
	}

	auto fdelta = (float)delta;
	const auto content_height = _resolution.height / height_ratio;
	const auto height_different = content_height - _resolution.height;

	if(_scroll_offset.y - fdelta > height_different)
	{
		fdelta = _scroll_offset.y - height_different;
	}

	if(_scroll_offset.y - fdelta < 0)
	{
		fdelta = _scroll_offset.y;
	}

	_scroll_offset.y -= fdelta;

	for (auto* element : *children())
	{
		element->move_by({ 0,fdelta * -1 });
	}

	Parent::handle_mouse_scroll(delta);
}
