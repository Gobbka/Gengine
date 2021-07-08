#include "UIManager.h"

#include <iostream>

#include "InteractiveForm.h"

UI::UIManager* UI::UIManager::instance()
{
	static auto* instance = new UIManager();
	return instance;
}

UI::InteractiveForm* UI::UIManager::create_layer(Render::D3DEngine* engine, Position2* lp_cursor)
{
	auto* form = new InteractiveForm(engine, lp_cursor);
	_forms.push_back(form);
	return form;
}

void UI::UIManager::on_lbmouse_down()
{
	
}

void UI::UIManager::on_lbmouse_up()
{
}

void UI::UIManager::on_mouse_scroll(short direction)
{
}

void UI::UIManager::on_mouse_move(int mx, int my)
{
	std::cout << mx << " " << my << '\n';
	for(auto*layer:_forms)
	{
		layer->on_mouse_move(mx, my);
	}
}
