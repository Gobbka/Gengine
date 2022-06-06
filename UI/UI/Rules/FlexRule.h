#pragma once
#include "ILocationRule.h"

namespace UI {

	enum class FlexDirection
	{
		Row,
		Column
	};

	enum class FlexWrap
	{
		Wrap,
		NoWrap
	};

	class __declspec(dllexport) FlexRule : public ILocationRule
	{
		ChildrenCollection* _children;
		Surface _ratios;

		void place_on_row(Position2 base_position, Surface resolution);
		void place_on_column(Position2 base_position, Surface resolution);
	public:
		void place_on(Position2 base_position, Surface resolution) override;

		explicit FlexRule(ChildrenCollection* children);
		// panel height / inner content height
		float height_ratio() const;
		Surface ratios() const;

		FlexDirection direction;
		FlexWrap wrap;
	};
}
