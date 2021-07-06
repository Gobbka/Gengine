#include "Panel.h"
#include "../../../../Render/Engine/Engine.h"
#include "../../InteractiveForm.h"

void Application::UI::Panel::draw(Render::DrawEvent* event)
{
	if(this->unique_id == 0x228)
	{
		this->unique_id = 0x228;
	}
	
	if(this->styles.overflow == VISIBLE_STATE_HIDDEN)
	{
		event->mask_draw_begin();
		event->set_alpha(this->alpha);
		event->draw_element(&this->rect);
		event->set_alpha(1.f);
		
		event->mask_discard_begin();
		Parent::draw(event);
		event->mask_discard_end();
	}else
	{
		event->mask_discard_begin(false);
		
		event->set_alpha(this->alpha);
		event->draw_element(&this->rect);
		event->set_alpha(1.f);
		Parent::draw(event);
		
		event->mask_discard_end(false);
	}
	
	//if(this->styles.overflow==VISIBLE_STATE_HIDDEN)
	//{
	//	auto* mask = event->engine->get_mask();
	//	mask->set_draw_mask();
	//	event->draw(4);
	//	mask->set_discard_mask();
	//}else
	//{
	//	event->draw(4);
	//}

	//Parent::draw(event);
	//
	//if (this->styles.overflow == VISIBLE_STATE_HIDDEN)
	//{
	//	auto* mask = event->engine->get_mask();
	//
	//	mask->unset_mask();
	//}
	
}

void Application::UI::Panel::on_initialize()
{
	this->form->add_canvas_element((Canvas::CanvasElement*) & rect);
	Parent::on_initialize();
}

Application::UI::ElementDescription Application::UI::Panel::get_desc()
{
	return ElementDescription(true, "PANEL");
}

Application::UI::Panel::Panel(Render::Position position, Render::Resolution resolution, Render::Color4 color)
	:
	Parent(position),
	rect(position,resolution,color)
{
	this->set_alpha(color.a);
}

bool Application::UI::Panel::point_belongs(Render::Position point)
{
	auto resolution = this->rect.get_resolution();
	auto position = this->rect.get_position();
	
	return
		(point.x >= position.x && point.x <= position.x + resolution.width) &&
		(point.y <= position.y && point.y >= (position.y - resolution.height));
}

void Application::UI::Panel::set_pos(float x, float y)
{
	auto pos = this->rect.get_position();
	float move_x = x - pos.x;
	float move_y = y - pos.y;
	this->move_by(move_x, move_y);
}

void Application::UI::Panel::set_color(Render::Color4 color)
{
	this->rect.set_color(color);
}

void Application::UI::Panel::move_by(float x, float y)
{
	this->rect.move_by(x, y);
	Parent::move_by(x, y);
}

Application::Render::Position Application::UI::Panel::get_position()
{
	return this->rect.get_position();
}


Application::UI::InteractiveElement* Application::UI::Panel::set_resolution(float width, float height)
{
	this->rect.set_resolution(width, height);
	return this;
}

Application::Render::Resolution Application::UI::Panel::get_resolution()
{
	return this->rect.get_resolution();
}
