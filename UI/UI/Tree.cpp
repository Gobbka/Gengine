#include "Tree.h"

#include "../Canvas/RenderEvent.h"

UI::TreeItem::TreeItem(Render::SpriteFont*font, const wchar_t* text)
	: text(font,text,{0,0})
{

}

UI::TreeItem::TreeItem(TreeItem& item)
	: text(item.text)
{

}

UI::TreeItem::TreeItem(TreeItem const& item)
	: text(item.text)
{

}

UI::TreeItem& UI::TreeItem::operator=(TreeItem const& item)
{
	text = std::move(Text(item.text));
	return *this;
}

UI::Tree::Tree(Render::SpriteFont*font,Position2 position)
	: _position(position)
	, _font(font)
{

}

void UI::Tree::add_item(const wchar_t* name)
{
	_items.push_back(std::move(TreeItem(_font, name)));
}

void UI::Tree::set_position(Position2 pos)
{
	_position = pos;
	for(auto& item : _items)
	{
		item.text.set_position(pos);
	}
}

void UI::Tree::set_resolution(Surface surface)
{
}

void UI::Tree::set_texture(Render::GETexture* texture)
{

}

void UI::Tree::move_by(Position2 pos)
{
	_position += pos;
	for (auto& item : _items)
	{
		item.text.move_by(pos);
	}
}

void UI::Tree::draw(Render::DrawEvent2D* event)
{
	event->draw_rect(_position, { 10,10 }, Color3XM::white());
	for (auto& item : _items)
	{
		((InteractiveElement&)item).draw(event);
	}
}

Position2 UI::Tree::get_position()
{
	return _position;
}

UI::ElementDescription UI::Tree::get_desc()
{
	return ElementDescription{ false,"Tree" };
}

Surface UI::Tree::get_resolution()
{
	return { 0,0 };
}

bool UI::Tree::point_belongs(Position2 point)
{
	return false;
}
