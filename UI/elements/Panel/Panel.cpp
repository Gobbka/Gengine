#include "Panel.h"
#include "../../InteractiveForm.h"
#include "Types/Types.h"

void UI::Panel::draw(Render::DrawEvent* event)
{
	if(this->unique_id == 0x228)
	{
		this->unique_id = 0x228;
	}
	
	if(this->styles.overflow == VisibleState::hidden)
	{
		event->mask_draw_begin();
		event->set_alpha(this->alpha);
		event->draw_object(&this->rect);
		event->set_alpha(1.f);
		
		event->mask_discard_begin();
		Parent::draw(event);
		event->mask_discard_end();
	}else
	{
		event->mask_discard_begin(false);
		
		event->set_alpha(this->alpha);
		event->draw_object(&this->rect);
		event->set_alpha(1.f);
		Parent::draw(event);
		
		event->mask_discard_end(false);
	}
}

void UI::Panel::on_initialize()
{
	form->add_object(&rect);
	Parent::on_initialize();
}

Color4 UI::Panel::get_color()
{
	return rect.get_color();
}

UI::ElementDescription UI::Panel::get_desc()
{
	return ElementDescription(true, "PANEL");
}

UI::Panel::Panel(Vector2 position,Surface resolution, Color4 color)
	:
	Parent(position),
	rect(color,position,resolution)
{
	this->set_alpha(color.a);
}

bool UI::Panel::point_belongs(Position2 point)
{
	auto resolution = this->rect.get_resolution();
	auto position = this->rect.get_position();
	
	return
		(point.x >= position.x && point.x <= position.x + resolution.width) &&
		(point.y <= position.y && point.y >= (position.y - resolution.height));
}

void UI::Panel::set_position(Position2 pos)
{
	auto local_pos = this->rect.get_position();

	this->move_by(Position2(pos.x - local_pos.x, pos.y - local_pos.y));
}

void UI::Panel::set_color(Color4 color)
{
	this->rect.set_color(color);
}

void UI::Panel::move_by(Position2 pos)
{
	this->rect.move_by(pos);
	
	UI::Parent::move_by(pos);
}

void UI::Panel::scale(float value)
{
	rect.scale(value);
}

void UI::Panel::set_texture(Render::Texture* texture)
{
	rect.set_texture(texture);
}

Position2 UI::Panel::get_position()
{
	return this->rect.get_position();
}


Surface UI::Panel::get_resolution()
{
	return this->rect.get_resolution();
}

void UI::Panel::set_resolution(Surface surface)
{
	this->rect.set_resolution(surface);
}
