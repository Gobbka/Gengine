#include "FlexRule.h"

#include "../../IElement/Parentable.h"

void UI::FlexRule::place_on_row(Position2 base_position, Surface resolution)
{
	float content_height = 0.f;
	auto last_position = base_position;
	auto own_position = base_position;

	for (auto* element : *_children)
	{
		auto element_res = element->get_resolution();

		if (last_position.x + element_res.width > own_position.x + resolution.width)
		{
			element->setPosition({ own_position.x,last_position.y - element_res.height });
			last_position.x = own_position.x;
			last_position.y -= element_res.height;
		}
		else
		{
			element->setPosition(last_position);

			last_position.x += element_res.width;
		}

		content_height = last_position.y - element_res.height;
	}

	content_height -= own_position.y;

	if (content_height * -1 > resolution.height)
	{
		_ratios.height = resolution.height / (content_height * -1);
	}
}

void UI::FlexRule::place_on_column(Position2 base_position, Surface resolution)
{
	auto last_pos = base_position;

	for (auto* element : *_children)
	{
		element->setPosition(Position2{ last_pos });
		auto old_resolution = element->get_resolution();
		element->set_resolution({ resolution.width,old_resolution.height });

		last_pos.y -= old_resolution.height;
	}
}

void UI::FlexRule::place_on(Position2 base_position, Surface resolution)
{
	if(direction == FlexDirection::Row)
	{
		return place_on_row(base_position, resolution);
	}

	if(direction == FlexDirection::Column)
	{
		return place_on_column(base_position, resolution);
	}
}

UI::FlexRule::FlexRule(ChildrenCollection* children)
	: _children(children)
	, _ratios(0,0)
	, direction(FlexDirection::Row)
	, wrap(FlexWrap::Wrap)
{
}

float UI::FlexRule::height_ratio() const
{
	return _ratios.height;
}

Surface UI::FlexRule::ratios() const
{
	return _ratios;
}
