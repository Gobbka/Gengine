#include "UIManager.h"

#include <iostream>

#include "InteractiveForm.h"

UI::UIManager::UIManager()
	: _cursor(0, 0)
{
}

UI::UIManager* UI::UIManager::instance()
{
	static auto* instance = new UIManager();
	return instance;
}

UI::InteractiveForm* UI::UIManager::create_layer(Render::D3DEngine* engine)
{
	auto* form = new InteractiveForm(engine, &_cursor);
	_forms.push_back(form);
	return form;
}

void UI::UIManager::on_lbmouse_down()
{
	for (auto* form : _forms)
		if (form->on_lbmouse_down() == Interaction::EventStatus::handled)
			return;
}

void UI::UIManager::on_lbmouse_up()
{
	for (auto* form : _forms)
		if (form->on_lbmouse_up() == Interaction::EventStatus::handled)
			return;
}

void UI::UIManager::on_mouse_scroll(short direction)
{
	for (auto* form : _forms)
		if (form->on_mouse_scroll(direction) == Interaction::EventStatus::handled)
			return;
}

void UI::UIManager::on_mouse_move(int mx, int my)
{
	_cursor = Position2(mx, my);
	
	for (auto iteration = _forms.size(); iteration --> 0;)
	{
		if (_forms[iteration]->on_mouse_move(mx,my) == Interaction::EventStatus::handled)
		{
			return;
		}
	}
}
