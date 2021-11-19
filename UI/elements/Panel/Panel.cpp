#include "Panel.h"
#include "../../InteractiveForm.h"
#include "../../Canvas/RenderEvent.h"
#include "Types/Types.h"

void UI::Panel::draw(Render::DrawEvent2D* event)
{	
	if (this->styles.overflow == VisibleState::hidden)
	{
		event->mask_draw_begin();
		event->set_alpha(this->alpha);
		event->draw_rect(_position, _resolution, _texture);
		
		event->set_alpha(1.f);

		event->mask_discard_begin();
		Parent::draw(event);
		event->mask_discard_end();
	}
	else
	{
		event->mask_discard_begin(false);

		event->set_alpha(this->alpha);
		event->draw_rect(_position, _resolution, _texture);
		event->set_alpha(1.f);
		Parent::draw(event);

		event->mask_discard_end(false);
	}
}

UI::ElementDescription UI::Panel::get_desc()
{
	return ElementDescription(true, "PANEL");
}

UI::Panel::Panel(Vector2 position,Surface resolution, Render::Texture* texture)
	: Parent(position)
	, _position(position)
	, _resolution(resolution)
	, _texture(texture)
{
	//this->set_alpha(color.a);
}

bool UI::Panel::point_belongs(Position2 point)
{
	auto resolution = _resolution;
	auto position = _position;
	
	return
		(point.x >= position.x && point.x <= position.x + resolution.width) &&
		(point.y <= position.y && point.y >= (position.y - resolution.height));
}

void UI::Panel::set_position(Position2 pos)
{
	_position = pos;
}

void UI::Panel::move_by(Position2 pos)
{
	_position += pos;

	UI::Parent::move_by(pos);
}

void UI::Panel::set_texture(Render::Texture* texture)
{
	_texture = texture;
}

Position2 UI::Panel::get_position()
{
	return _position;
}


Surface UI::Panel::get_resolution()
{
	return _resolution;
}

void UI::Panel::set_resolution(Surface surface)
{
	_resolution = surface;
}
