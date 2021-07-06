#pragma once
#include "../Panel/Panel.h"

namespace Application
{
	namespace UI
	{
		class ItemList : public Panel
		{
		public:
			void on_initialize() override;
			int list_offset = 0;
			ItemList(Render::Position position, Render::Resolution resolution, Render::Color4 color);
		public:
			ElementDescription get_desc() override;

			void handle_mouse_scroll(int delta) override;
		};
	}
}
