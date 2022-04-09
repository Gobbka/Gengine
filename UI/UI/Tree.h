#pragma once
#include <vector>

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

	class __declspec(dllexport) Tree final : public InteractiveElement {
		Position2 _position;
		Render::SpriteFont* _font;
		std::vector<TreeItem> _items{};
	public:
		Tree(Render::SpriteFont*font, Position2 position);

		void add_item(const wchar_t* name);

		void set_position(Position2 pos) override;
		void set_resolution(Surface surface) override;
		void set_texture(Render::GETexture* texture) override;
		void move_by(Position2) override;
		void draw(Render::DrawEvent2D* event) override;
		Position2 get_position() override;
		ElementDescription get_desc() override;
		Surface get_resolution() override;
		bool point_belongs(Position2 point) override;
	};
}