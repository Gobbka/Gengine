#include "ItemList.h"

void Application::UI::ItemList::on_initialize()
{
	Panel::on_initialize();

	auto this_resolution = this->get_resolution();

	float offset = 0;
	Panel::children()->foreach([&](InteractiveElement* element)
		{
			auto element_resolution = element->get_resolution();
			auto margin = element->styles.margin;
			element->set_resolution(
				this_resolution.width - margin.x - margin.z,
				element_resolution.height
			);
			element->move_by(margin.x, offset - margin.y);

			offset -= (element_resolution.height + margin.y + margin.w);
		});
}

Application::UI::ItemList::ItemList(Render::Position position, Render::Resolution resolution, Render::Color4 color)
	: Panel(position,resolution,color)
{
	Panel::styles.overflow = VISIBLE_STATE_HIDDEN;
}

Application::UI::ElementDescription Application::UI::ItemList::get_desc()
{
	return ElementDescription( true,"ItemList" ,false);
}

void Application::UI::ItemList::handle_mouse_scroll(int delta)
{
	delta /= 120;
	Panel::handle_mouse_scroll(delta);
	
	if(this->list_offset - delta < 0)
	{
		delta = list_offset;
	}

	list_offset -= delta;
	
	Panel::children()->foreach([delta](InteractiveElement* element)
		{
			element->move_by(0, (float)delta*-1);
		});
	
	const auto cursor_long = Application::Context::point_to_center(Context::get_client_cursor_point());

	Panel::handle_mouse_move(cursor_long.x, cursor_long.y);
}
