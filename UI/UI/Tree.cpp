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
	: FlexColumnPanel(position,{500,300},{1,1,1})
	, _font(font)
{

}

void UI::Tree::add_item(const wchar_t* name)
{
	add_element(new Text(_font, name, { 0,10 }));
}

UI::ElementDescription UI::Tree::getDesc()
{
	return ElementDescription{ true,"TREE" };
}
