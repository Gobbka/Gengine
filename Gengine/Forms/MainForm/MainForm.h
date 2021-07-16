#pragma once
#include "../Form/Form.h"
namespace Core {
	class GraphicsContext;
}

namespace UI {
	class Panel;
}

namespace Forms
{
	class MainForm : public Core::Form
	{
	private:
		UI::Panel* _topbar_panel;
		UI::Panel* _worldspace_panel;
		UI::Panel* _assets_panel;
	public:
		MainForm(HINSTANCE hinst, UINT width, UINT height);

		void handle_resize(Surface rect) override;
		
		void initialize_components(Core::GraphicsContext*graphics);
	};
}
