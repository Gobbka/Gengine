#include "FlexRowPanel.h"

#include "../../Canvas/RenderEvent.h"
#include "Types/Types.h"

void UI::FlexRowPanel::draw(Render::DrawEvent2D* event)
{
	if (this->styles.overflow == VisibleState::hidden)
	{
		event->mask_draw_begin();
		event->set_alpha(this->alpha);

		if (_texture)
			event->draw_rect(_position, _resolution, _texture);
		else
			event->draw_rect(_position, _resolution, _color);

		event->set_alpha(1.f);
		event->mask_discard_begin();
		Parent::draw(event);
		event->mask_discard_end();
	}
	else
	{
		event->mask_discard_begin(false);

		event->set_alpha(this->alpha);
		if (_texture)
			event->draw_rect(_position, _resolution, _texture);
		else
			event->draw_rect(_position, _resolution, _color);
		event->set_alpha(1.f);
		Parent::draw(event);

		event->mask_discard_end(false);
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
{}

UI::FlexRowPanel::FlexRowPanel(Vector2 position, Surface resolution, Color3XM color)
	: Parent(position)
	, _position(position)
	, _resolution(resolution)
	, _texture(nullptr)
	, _color(color)
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

	return this;
}
