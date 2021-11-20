#include "FlexRowPanel.h"

#include "../../Canvas/RenderEvent.h"
#include "Types/Types.h"

void UI::FlexRowPanel::draw(Render::DrawEvent2D* event)
{

	event->mask_draw_begin();
	event->set_alpha(this->alpha);

	if (_texture)
		event->draw_rect(_position, _resolution, _texture);
	else
		event->draw_rect(_position, _resolution, _color);

	event->set_alpha(1.f);
	event->mask_discard_begin(false);
	Parent::draw(event);
	event->mask_discard_end(true);

	if (_scroll_bar_height > 0)
	{
		auto resolution = get_resolution();
		auto position = get_position();

		const auto scroll_bar_width = 20;
		const auto scroll_bar_height_px = resolution.height * _scroll_bar_height;

		event->draw_rect(
			{ position.x+resolution.width - scroll_bar_width - 5,position.y -5 }, 
			{ scroll_bar_width,scroll_bar_height_px-10 },
			Color3XM::from_rgb(62, 62, 62)
		);
	}
}

UI::ElementDescription UI::FlexRowPanel::get_desc()
{
	return ElementDescription(true, "FLEXROWPANEL");
}

UI::FlexRowPanel::FlexRowPanel(Vector2 position, Surface resolution, Render::Texture* texture)
	: Parent(position)
	, _position(position)
	, _resolution(resolution)
	, _texture(texture)
	, _color(1, 1, 1)
	, _scroll_bar_height(1)
{}

UI::FlexRowPanel::FlexRowPanel(Vector2 position, Surface resolution, Color3XM color)
	: Parent(position)
	, _position(position)
	, _resolution(resolution)
	, _texture(nullptr)
	, _color(color)
	, _scroll_bar_height(1)
{}

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

	UI::Parent::move_by(pos);
}

void UI::FlexRowPanel::set_texture(Render::Texture* texture)
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

UI::Parent* UI::FlexRowPanel::add_element(InteractiveElement* element)
{
	if (element->have_parent())
		return this;

	element->set_parent(this);
	element->move_by(this->get_position());

	auto* last_element = children()->last();
	children()->append(element);

	if (last_element != nullptr)
	{
		auto relative_point = last_element->point_to(this);
		auto element_res = last_element->get_resolution();

		if (
			relative_point.x + element_res.width +
			element->styles.margin.w + element->styles.margin.y +
			element->get_resolution().width > get_resolution().width
			)
		{
			element->move_by({ 0,relative_point.y - element_res.height });
		}
		else
		{
			element->move_by({ relative_point.x + element_res.width,relative_point.y });
		}
	}

	auto element_pos = element->point_to(this);
	auto element_res = element->get_resolution();

	if((element_pos.y - element_res.height)*-1 > _resolution.height)
	{
		_scroll_bar_height = _resolution.height / ((element_pos.y - element_res.height) * -1);
	}

	return this;
}

void UI::FlexRowPanel::handle_mouse_scroll(int delta)
{
	children()->foreach([&](InteractiveElement* element)
		{
			element->move_by({ 0,(float)delta * -1 });
		});

	Parent::handle_mouse_scroll(delta);
}
