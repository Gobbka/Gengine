#pragma once
#include <vector>

#include "FlexColumnPanel.h"
#include "../IElement/InteractiveElement.h"
#include "Text.h"

namespace UI
{
	struct __declspec(dllexport) TreeItem {
		Text text;

		TreeItem(Render::SpriteFont*font, const wchar_t* text);
		TreeItem(TreeItem& item);
		explicit TreeItem(TreeItem const& item);
		TreeItem& operator=(TreeItem const& item);
	};

	class __declspec(dllexport) Tree final : public FlexColumnPanel {
		Render::SpriteFont* _font;
		std::vector<TreeItem> _items{};
	public:
		Tree(Render::SpriteFont*font, Position2 position);

		void add_item(const wchar_t* name);

		ElementDescription get_desc() override;
	};
}